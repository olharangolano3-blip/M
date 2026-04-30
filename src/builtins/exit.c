/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:29:36 by adjigo            #+#    #+#             */
/*   Updated: 2026/04/26 12:00:00 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	exit_invalid(t_cmd *cmd, t_shell *shell)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->argv[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	shell->should_exit = 1;
	shell->exit_status = 255;
	return (255);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	int	code;

	ft_putstr_fd("exit\n", 1);
	if (cmd->argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (cmd->argc == 1)
	{
		shell->should_exit = 1;
		return (shell->exit_status);
	}
	if (!is_numeric(cmd->argv[1]))
		return (exit_invalid(cmd, shell));
	code = ft_atoi(cmd->argv[1]) % 256;
	if (code < 0)
		code += 256;
	shell->should_exit = 1;
	shell->exit_status = code;
	return (code);
}
