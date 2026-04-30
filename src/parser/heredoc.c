/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <adjigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:33:35 by dalde-ol          #+#    #+#             */
/*   Updated: 2026/04/30 11:38:04 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	heredoc_write(t_redir *redir, char *line, int fd, t_shell *shell)
{
	char	*expanded;

	if (redir->expand)
		expanded = expand_word(line, shell);
	else
		expanded = line;
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	if (redir->expand && expanded != line)
		free(expanded);
}

static void	heredoc_sigint(int sig)
{
	g_signal = sig;
	rl_done =  1;
	write(1, "\n", 1);
}

static void	heredoc_child(t_redir *redir, int fd[2], t_shell *shell,
		t_parse_ctx *ctx)
{
	char	*line;
	int		interrupted;

	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	interrupted = 0;
	while (1)
	{
		g_signal = 0;
		line = readline("> ");
		if (!line || g_signal == SIGINT)
		{
			if (line)
				free(line);
			interrupted = (g_signal == SIGINT);
			break ;
		}
		if (ft_strncmp(line, redir->file, ft_strlen(redir->file) + 1) == 0)
		{
			free(line);
			break ;
		}
		heredoc_write(redir, line, fd[1], shell);
		free(line);
	}
	close(fd[1]);
	free(redir->file);
	free(redir);
	tokens_free(ctx->tokens);
	pipeline_free(ctx->pipeline);
	cmd_free(ctx->cmd);
	env_free(shell->env);
	if (interrupted)
	{
		signal(SIGINT, SIG_DFL);
		kill(getpid(), SIGINT);
	}
	exit(0);
}

static int	heredoc_wait(pid_t pid, int fd_read)
{
	int	status;
	int	result;

	signal(SIGINT, SIG_IGN);
	result = waitpid(pid, &status, 0);
	while (result == -1 && errno == EINTR)
		result = waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	if (result == -1 || WIFSIGNALED(status))
	{
		if(WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			g_signal = SIGINT;
		close(fd_read);
		return (-1);
	}
	return (0);
}

int	heredoc_read(t_redir *redir, t_shell *shell, t_parse_ctx *ctx)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
		heredoc_child(redir, fd, shell, ctx);
	close(fd[1]);
	if (heredoc_wait(pid, fd[0]) == -1)
		return (-1);
	redir->heredoc_fd = fd[0];
	return (0);
}
