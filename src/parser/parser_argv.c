/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:00:00 by dalde-ol          #+#    #+#             */
/*   Updated: 2026/04/20 12:00:00 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	**argv_grow(char **old_argv, int old_argc)
{
	char	**new_argv;
	int		i;

	new_argv = malloc(sizeof(char *) * (old_argc + 2));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < old_argc)
	{
		new_argv[i] = old_argv[i];
		i++;
	}
	new_argv[old_argc] = NULL;
	new_argv[old_argc + 1] = NULL;
	free(old_argv);
	return (new_argv);
}

int	cmd_add_argv(t_cmd *cmd, char *value)
{
	char	**new_argv;
	char	*dup;

	new_argv = argv_grow(cmd->argv, cmd->argc);
	if (!new_argv)
		return (-1);
	dup = ft_strdup(value);
	if (!dup)
	{
		free(new_argv);
		return (-1);
	}
	new_argv[cmd->argc] = dup;
	new_argv[cmd->argc + 1] = NULL;
	cmd->argv = new_argv;
	cmd->argc++;
	return (0);
}

void	cmd_add_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	*ptr;

	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return ;
	}
	ptr = cmd->redirs;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = redir;
}

void	pipeline_add_cmd(t_pipeline *pipeline, t_cmd *cmd)
{
	t_cmd	*ptr;

	pipeline->count++;
	if (!pipeline->cmds)
	{
		pipeline->cmds = cmd;
		return ;
	}
	ptr = pipeline->cmds;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = cmd;
}
