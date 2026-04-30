/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:29:27 by adjigo            #+#    #+#             */
/*   Updated: 2026/04/20 12:00:00 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	builtin_env(t_cmd *cmd, t_shell *shell)
{
	int	i;

	(void)cmd;
	i = 0;
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
		{
			ft_putstr_fd(shell->env[i], 1);
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
