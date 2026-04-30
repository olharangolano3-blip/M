/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <adjigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:05:52 by adjigo            #+#    #+#             */
/*   Updated: 2026/04/30 09:47:20 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_valid_identifier(const char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_list(t_shell *shell)
{
	char	*ep;
	int		i;

	i = 0;
	while (shell->env[i])
	{
		ep = ft_strchr(shell->env[i], '=');
		if (ep)
		{
			ft_putstr_fd("declare -x ", 1);
			write(1, shell->env[i], ep - shell->env[i] + 1);
			write(1, "\"", 1);
			ft_putstr_fd(ep + 1, 1);
			write(1, "\"\n", 2);
		}
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(shell->env[i], 1);
			write(1, "\n", 1);
		}
		i++;
	}
}

static int	export_no_value(const char *arg, t_shell *shell)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd((char *)arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (env_export_name(shell, arg) == -1)
	{
		return (1);
	}
	return (0);
}

static int	export_with_value(const char *arg, t_shell *shell)
{
	char	*eq;
	char	*name;
	int		ret;

	eq = ft_strchr(arg, '=');
	name = ft_substr(arg, 0, eq - arg);
	if (!name)
		return (1);
	if (!is_valid_identifier(name))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd((char *)arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(name);
		return (1);
	}
	ret = env_set(shell, name, eq + 1);
	free(name);
	if (ret == -1)
		return (1);
	else
		return (0);
	return (0);
}

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	ret;

	if (cmd->argc == 1)
	{
		print_export_list(shell);
		return (0);
	}
	ret = 0;
	i = 1;
	while (cmd->argv[i])
	{
		if (ft_strchr(cmd->argv[i], '='))
			ret |= export_with_value(cmd->argv[i], shell);
		else
			ret |= export_no_value(cmd->argv[i], shell);
		i++;
	}
	return (ret);
}
