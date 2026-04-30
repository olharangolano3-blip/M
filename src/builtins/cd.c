/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:29:17 by adjigo            #+#    #+#             */
/*   Updated: 2026/04/20 12:00:00 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	update_pwd(t_shell *shell, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = NULL;
	if (old_pwd)
		env_set(shell, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		env_set(shell, "PWD", new_pwd);
		free(new_pwd);
	}
}

static int	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
	return (1);
}

int	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	*old_pwd;

	if (cmd->argc == 1)
	{
		path = env_get(shell->env, "HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		path = cmd->argv[1];
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		free(old_pwd);
		return (cd_error(path));
	}
	update_pwd(shell, old_pwd);
	free(old_pwd);
	return (0);
}
