/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <adjigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 12:00:00 by adjigo            #+#    #+#             */
/*   Updated: 2026/04/26 12:00:00 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	child_exit(t_shell *shell, t_pipeline *pipeline, int code)
{
	env_free(shell->env);
	pipeline_free(pipeline);
	exit(code);
}

static void	free_dirs(char **dirs)
{
	int	i;

	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
}

char	*free_dirs_return(char **dirs, char *full)
{
	free_dirs(dirs);
	return (full);
}

int	wait_children(pid_t *pids, int count)
{
	int	status;
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (exit_code);
}

void	init_ctx(t_exec_ctx *ctx, t_pipeline *pipeline,
		int pipe_count, int pipes[][2])
{
	ctx->pipe_count = pipe_count;
	ctx->pipes = pipes;
	ctx->pipeline = pipeline;
	ctx->pipe_idx = 0;
}
