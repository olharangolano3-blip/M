/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:49:16 by adjigo            #+#    #+#             */
/*   Updated: 2026/04/20 12:00:00 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	apply_redir_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), -1);
	close(fd);
	return (0);
}

static int	apply_redir_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), -1);
	close(fd);
	return (0);
}

static int	apply_redir_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), -1);
	close(fd);
	return (0);
}

static int	apply_redir_heredoc(t_redir *redir)
{
	if (dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
		return (-1);
	close(redir->heredoc_fd);
	redir->heredoc_fd = -1;
	return (0);
}

int	apply_redirections(t_redir *redirs)
{
	t_redir	*r;

	r = redirs;
	while (r)
	{
		if (r->type == TOKEN_REDIR_IN && apply_redir_in(r) == -1)
			return (-1);
		else if (r->type == TOKEN_REDIR_OUT && apply_redir_out(r) == -1)
			return (-1);
		else if (r->type == TOKEN_REDIR_APPEND && apply_redir_append(r) == -1)
			return (-1);
		else if (r->type == TOKEN_HEREDOC && apply_redir_heredoc(r) == -1)
			return (-1);
		r = r->next;
	}
	return (0);
}
