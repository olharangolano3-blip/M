/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:00:00 by dalde-ol          #+#    #+#             */
/*   Updated: 2026/04/20 12:00:00 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_pipeline	*pipeline_new(void)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->cmds = NULL;
	pipeline->count = 0;
	return (pipeline);
}

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->redirs = NULL;
	cmd->cmd_path = NULL;
	cmd->is_builtin = false;
	cmd->next = NULL;
	return (cmd);
}

static char	*heredoc_delim(char *raw, int *expand)
{
	int	len;

	len = ft_strlen(raw);
	if ((raw[0] == '\'' && raw[len - 1] == '\'')
		|| (raw[0] == '"' && raw[len - 1] == '"'))
	{
		*expand = 0;
		return (ft_substr(raw, 1, len - 2));
	}
	*expand = 1;
	return (ft_strdup(raw));
}

t_redir	*redir_new(t_token_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->heredoc_fd = -1;
	redir->next = NULL;
	if (type == TOKEN_HEREDOC)
		redir->file = heredoc_delim(file, &redir->expand);
	else
	{
		redir->file = ft_strdup(file);
		redir->expand = 1;
	}
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}
