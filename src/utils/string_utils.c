/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <adjigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:00:00 by adjigo            #+#    #+#             */
/*   Updated: 2026/04/24 14:23:57 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	execute_builtin(t_pipeline *pipeline, t_shell *shell)
{
	int	saved_in;
	int	saved_out;
	int	ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirections(pipeline->cmds->redirs) == -1)
	{
		close(saved_in);
		close(saved_out);
		shell->exit_status = 1;
		return (1);
	}
	ret = run_builtin(pipeline->cmds, shell);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
	shell->exit_status = ret;
	return (ret);
}

int	execute(t_pipeline *pipeline, t_shell *shell)
{
	int	pipes[64][2];
	int	pipe_count;

	pipe_count = pipeline->count - 1;
	if (pipeline->count == 1
		&& pipeline->cmds->argv
		&& pipeline->cmds->argv[0]
		&& is_builtin(pipeline->cmds->argv[0]))
		return (execute_builtin(pipeline, shell));
	if (pipe_count > 0 && setup_pipes(pipe_count, pipes) == -1)
	{
		shell->exit_status = 1;
		return (1);
	}
	shell->exit_status = fork_pipeline(pipeline, shell, pipe_count, pipes);
	return (shell->exit_status);
}
