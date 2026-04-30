/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <adjigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:58:53 by adjigo            #+#    #+#             */
/*   Updated: 2026/04/26 12:00:00 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*find_in_dirs(char **dirs, char *cmd)
{
	char	*full;
	char	*tmp;
	int		i;

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full)
			return (free_dirs_return(dirs, NULL));
		if (access(full, X_OK) == 0)
			return (free_dirs_return(dirs, full));
		free(full);
		i++;
	}
	return (free_dirs_return(dirs, NULL));
}

char	*resolve_path(char *cmd, char **env)
{
	char	**dirs;
	char	*path_env;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = env_get(env, "PATH");
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	return (find_in_dirs(dirs, cmd));
}

static void	exec_connect_pipes(int pipe_index, int pipe_count, int pipes[][2])
{
	if (pipe_index > 0)
		dup2(pipes[pipe_index - 1][0], STDIN_FILENO);
	if (pipe_index < pipe_count)
		dup2(pipes[pipe_index][1], STDOUT_FILENO);
	close_pipes(pipe_count, pipes);
}

static void	exec_child(t_cmd *cmd, t_shell *shell, t_exec_ctx *ctx)
{
	int	ret;

	exec_connect_pipes(ctx->pipe_idx, ctx->pipe_count, ctx->pipes);
	if (apply_redirections(cmd->redirs) == -1)
		child_exit(shell, ctx->pipeline, 1);
	if (!cmd->argv || !cmd->argv[0])
		child_exit(shell, ctx->pipeline, 0);
	if (is_builtin(cmd->argv[0]))
	{
		signal(SIGPIPE, SIG_IGN);
		ret = run_builtin(cmd, shell);
		child_exit(shell, ctx->pipeline, ret);
	}
	cmd->cmd_path = resolve_path(cmd->argv[0], shell->env);
	if (!cmd->cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		child_exit(shell, ctx->pipeline, 127);
	}
	execve(cmd->cmd_path, cmd->argv, shell->env);
	ft_putstr_fd("minishell: execve failed\n", 2);
	child_exit(shell, ctx->pipeline, 126);
}

int	fork_pipeline(t_pipeline *pipeline, t_shell *shell,
		int pipe_count, int pipes[][2])
{
	pid_t		pids[64];
	t_exec_ctx	ctx;
	t_cmd		*cmd;
	pid_t		pid;

	init_ctx(&ctx, pipeline, pipe_count, pipes);
	cmd = pipeline->cmds;
	while (cmd)
	{
		pid = fork();
		pids[ctx.pipe_idx] = pid;
		if (pid == -1)
			return (close_pipes(pipe_count, pipes), 1);
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			exec_child(cmd, shell, &ctx);
		}
		cmd = cmd->next;
		ctx.pipe_idx++;
	}
	close_pipes(pipe_count, pipes);
	return (wait_children(pids, pipeline->count));
}
