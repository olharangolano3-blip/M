/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:43:24 by dalde-ol          #+#    #+#             */
/*   Updated: 2026/04/20 12:00:00 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_redirs(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
			ft_putstr_fd("    redir : < ", 1);
		else if (redir->type == TOKEN_REDIR_OUT)
			ft_putstr_fd("    redir : > ", 1);
		else if (redir->type == TOKEN_REDIR_APPEND)
			ft_putstr_fd("    redir : >> ", 1);
		else if (redir->type == TOKEN_HEREDOC)
			ft_putstr_fd("    redir : << ", 1);
		ft_putstr_fd(redir->file, 1);
		write(1, "\n", 1);
		redir = redir->next;
	}
}

static void	print_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		ft_putstr_fd("    argv: ", 1);
		ft_putstr_fd(argv[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

static void	print_cmd(t_cmd *cmd, int index)
{
	char	*idx;

	idx = ft_itoa(index);
	ft_putstr_fd("-- CMD [", 1);
	ft_putstr_fd(idx, 1);
	free(idx);
	if (cmd->argc > 0)
	{
		ft_putstr_fd("] -- ", 1);
		ft_putstr_fd(cmd->argv[0], 1);
	}
	else
		ft_putstr_fd("] -- (no cmd)", 1);
	write(1, "\n", 1);
	print_argv(cmd->argv);
	if (cmd->redirs)
		print_redirs(cmd->redirs);
	ft_putstr_fd("-------------------------\n", 1);
}

static void	print_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		print_cmd(cmd, i);
		if (cmd->next)
			ft_putstr_fd("          | PIPE\n", 1);
		cmd = cmd->next;
		i++;
	}
}

void	pipeline_print(t_pipeline *pipeline)
{
	char	*count;

	if (!pipeline)
		return ;
	count = ft_itoa(pipeline->count);
	ft_putstr_fd("=== PIPELINE (", 1);
	ft_putstr_fd(count, 1);
	free(count);
	ft_putstr_fd(" cmd(s)) ===\n", 1);
	print_cmds(pipeline->cmds);
	ft_putstr_fd("===========================\n", 1);
}
