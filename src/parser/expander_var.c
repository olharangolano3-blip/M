/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <adjigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:00:00 by dalde-ol          #+#    #+#             */
/*   Updated: 2026/04/27 08:35:53 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	var_name_len(const char *str, int i)
{
	int	len;

	len = 0;
	if (str[i] == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		len++;
		i++;
	}
	return (len);
}

char	*get_var_value(const char *str, int *i, t_shell *shell)
{
	int		len;
	char	*name;
	char	*val;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	len = var_name_len(str, *i);
	if (len == 0)
		return (ft_strdup("$"));
	name = ft_substr(str, *i, len);
	if (!name)
		return (NULL);
	*i += len;
	val = env_get(shell->env, name);
	free(name);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

char	*get_segment(char *word, int *i, t_shell *shell)
{
	if (word[*i] == '\'')
		return (get_single(word, i));
	else if (word[*i] == '"')
		return (process_double_quote(word, i, shell));
	else
		return (process_unquoted(word, i, shell));
}
