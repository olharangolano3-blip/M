/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:00:00 by dalde-ol          #+#    #+#             */
/*   Updated: 2026/04/20 12:00:00 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	redir_free(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		free(redir->file);
		if (redir->heredoc_fd != -1)
			close(redir->heredoc_fd);
		free(redir);
		redir = next;
	}
}

static void	argv_free(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	cmd_free(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		argv_free(cmd->argv);
		redir_free(cmd->redirs);
		free(cmd->cmd_path);
		free(cmd);
		cmd = next;
	}
}

void	pipeline_free(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	cmd_free(pipeline->cmds);
	free(pipeline);
}
