/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <adjigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:00:00 by dalde-ol          #+#    #+#             */
/*   Updated: 2026/04/30 11:06:47 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	parse_redir(t_token **token, t_cmd *cmd, t_shell *shell,
		t_parse_ctx *ctx)
{
	t_redir	*redir;
	t_token	*next;

	next = (*token)->next;
	if (!next || next->type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected"
			" token `newline'\n", 2);
		return (-1);
	}
	redir = redir_new((*token)->type, next->value);
	if (!redir)
		return (-1);
	if (redir->type == TOKEN_HEREDOC && heredoc_read(redir, shell, ctx) == -1)
	{
		free(redir->file);
		free(redir);
		return (-1);
	}
	cmd_add_redir(cmd, redir);
	*token = next;
	return (0);
}

static int	parse_token(t_token **token, t_cmd *cmd, t_shell *shell,
		t_parse_ctx *ctx)
{
	if ((*token)->type == TOKEN_WORD)
		return (cmd_add_argv(cmd, (*token)->value));
	if ((*token)->type != TOKEN_PIPE)
		return (parse_redir(token, cmd, shell, ctx));
	return (0);
}

static t_cmd	*handle_pipe(t_cmd *cmd, t_pipeline *pipeline)
{
	if (cmd->argc == 0 && !cmd->redirs)
	{
		cmd_free(cmd);
		ft_putstr_fd("minishell: syntax error near unexpected"
			" token `|'\n", 2);
		return (NULL);
	}
	pipeline_add_cmd(pipeline, cmd);
	return (cmd_new());
}

static t_cmd	*parse_cmds(t_token *tokens, t_token *token,
				t_pipeline *pipeline, t_shell *shell)
{
	t_cmd		*cmd;
	t_parse_ctx	ctx;

	cmd = cmd_new();
	if (!cmd)
		return (NULL);
	ctx.tokens = tokens;
	ctx.pipeline = pipeline;
	while (token)
	{
		if (token->type == TOKEN_PIPE)
		{
			cmd = handle_pipe(cmd, pipeline);
			if (!cmd)
				return (NULL);
		}
		else
		{
			ctx.cmd = cmd;
			if (parse_token(&token, cmd, shell, &ctx) == -1)
			{
				cmd_free(cmd);
				return (NULL);
			}
		}
		token = token->next;
	}
	return (cmd);
}

t_pipeline	*parse(t_token *tokens, t_shell *shell)
{
	t_pipeline	*pipeline;
	t_cmd		*last_cmd;

	pipeline = pipeline_new();
	if (!pipeline)
		return (NULL);
	last_cmd = parse_cmds(tokens, tokens, pipeline, shell);
	if (!last_cmd)
	{
		pipeline_free(pipeline);
		return (NULL);
	}
	if (last_cmd->argc == 0 && !last_cmd->redirs)
	{
		cmd_free(last_cmd);
		pipeline_free(pipeline);
		ft_putstr_fd("minishell: syntax error near unexpected"
			" token `|'\n", 2);
		return (NULL);
	}
	pipeline_add_cmd(pipeline, last_cmd);
	return (pipeline);
}
