/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:00:00 by dalde-ol          #+#    #+#             */
/*   Updated: 2026/04/26 12:00:00 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*append_segment(char *result, char *val)
{
	char	*tmp;

	tmp = ft_strjoin(result, val);
	free(result);
	free(val);
	return (tmp);
}

char	*process_double_quote(const char *str, int *i, t_shell *shell)
{
	char	*result;
	char	*val;

	(*i)++;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			val = get_var_value(str, i, shell);
		else
		{
			val = ft_substr(str, *i, 1);
			(*i)++;
		}
		if (!val)
			return (free(result), NULL);
		result = append_segment(result, val);
		if (!result)
			return (NULL);
	}
	if (str[*i] == '"')
		(*i)++;
	return (result);
}

char	*process_unquoted(const char *str, int *i, t_shell *shell)
{
	char	*result;
	char	*val;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[*i] && str[*i] != '\'' && str[*i] != '"')
	{
		if (str[*i] == '$')
			val = get_var_value(str, i, shell);
		else
		{
			val = ft_substr(str, *i, 1);
			(*i)++;
		}
		if (!val)
			return (free(result), NULL);
		result = append_segment(result, val);
		if (!result)
			return (NULL);
	}
	return (result);
}
