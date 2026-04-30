/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <adjigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:00:00 by dalde-ol          #+#    #+#             */
/*   Updated: 2026/04/30 09:43:57 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	env_export_name(t_shell *shell, const char *name)
{
	int	len;
	int	i;

	len = ft_strlen(name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& (shell->env[i][len] == '=' || shell->env[i][len] == '\0'))
			return (0);
		i++;
	}
	return (env_add(shell, name));
}

int	env_add(t_shell *shell, const char *entry)
{
	char	**new_env;
	int		len;
	int		i;

	len = env_count(shell->env);
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (-1);
	i = 0;
	while (i < len)
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[len] = ft_strdup(entry);
	if (!new_env[len])
		return (free(new_env), -1);
	new_env[len + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

static char	*build_entry(const char *name, const char *val)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	entry = ft_strjoin(tmp, val);
	free(tmp);
	return (entry);
}

static int	env_update(t_shell *shell, const char *name, const char *val)
{
	char	*entry;
	int		len;
	int		i;

	len = ft_strlen(name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& shell->env[i][len] == '=')
		{
			entry = build_entry(name, val);
			if (!entry)
				return (-1);
			free(shell->env[i]);
			shell->env[i] = entry;
			return (1);
		}
		i++;
	}
	return (0);
}

int	env_set(t_shell *shell, const char *name, const char *val)
{
	char	*entry;
	int		ret;

	ret = env_update(shell, name, val);
	if (ret == 1)
		return (0);
	if (ret == -1)
		return (-1);
	entry = build_entry(name, val);
	if (!entry)
		return (-1);
	ret = env_add(shell, entry);
	free(entry);
	return (ret);
}
