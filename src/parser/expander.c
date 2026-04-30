/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <adjigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:00:00 by dalde-ol          #+#    #+#             */
/*   Updated: 2026/04/27 08:32:39 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*append_segment(char *result, char *val);
char	*process_double_quote(const char *str, int *i, t_shell *shell);
char	*process_unquoted(const char *str, int *i, t_shell *shell);

char	*get_single(char *word, int *i)
{
	int		start;
	char	*content;

	(*i)++;
	start = *i;
	while (word[*i] && word[*i] != '\'')
		(*i)++;
	content = ft_substr(word, start, *i - start);
	if (word[*i] == '\'')
		(*i)++;
	return (content);
}

static int	expand_redirs(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	char	*expanded;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type != TOKEN_HEREDOC)
		{
			expanded = expand_word(redir->file, shell);
			if (!expanded)
				return (-1);
			free(redir->file);
			redir->file = expanded;
		}
		redir = redir->next;
	}
	return (0);
}

static int	expand_argv(t_cmd *cmd, t_shell *shell)
{
	char	*expanded;
	int		i;

	i = 0;
	while (i < cmd->argc)
	{
		expanded = expand_word(cmd->argv[i], shell);
		if (!expanded)
			return (-1);
		free(cmd->argv[i]);
		cmd->argv[i] = expanded;
		i++;
	}
	return (0);
}

char	*expand_word(char *word, t_shell *shell)
{
	char	*result;
	char	*segment;
	char	*tmp;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (word[i])
	{
		segment = get_segment(word, &i, shell);
		if (!segment)
			return (free(result), NULL);
		tmp = ft_strjoin(result, segment);
		free(result);
		free(segment);
		result = tmp;
		if (!result)
			return (NULL);
	}
	return (result);
}

int	expand(t_pipeline *pipeline, t_shell *shell)
{
	t_cmd	*cmd;

	cmd = pipeline->cmds;
	while (cmd)
	{
		if (expand_argv(cmd, shell) == -1)
			return (-1);
		if (expand_redirs(cmd, shell) == -1)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}
