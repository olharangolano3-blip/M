/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:00:00 by adjigo            #+#    #+#             */
/*   Updated: 2026/04/20 12:00:00 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strncmp(cmd, "echo", 5) == 0
		|| ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0
		|| ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0);
}

int	run_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*name;

	name = cmd->argv[0];
	if (ft_strncmp(name, "echo", 5) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(name, "cd", 3) == 0)
		return (builtin_cd(cmd, shell));
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (builtin_pwd(cmd));
	if (ft_strncmp(name, "export", 7) == 0)
		return (builtin_export(cmd, shell));
	if (ft_strncmp(name, "unset", 6) == 0)
		return (builtin_unset(cmd, shell));
	if (ft_strncmp(name, "env", 4) == 0)
		return (builtin_env(cmd, shell));
	if (ft_strncmp(name, "exit", 5) == 0)
		return (builtin_exit(cmd, shell));
	return (127);
}
