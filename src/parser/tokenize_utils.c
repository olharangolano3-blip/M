/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:19:27 by dalde-ol          #+#    #+#             */
/*   Updated: 2026/04/20 12:00:00 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*token_new(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->next = NULL;
	if (value)
	{
		token->value = ft_strdup(value);
		if (!token->value)
		{
			free(token);
			return (NULL);
		}
	}
	else
		token->value = NULL;
	return (token);
}

void	token_add_back(t_token **token_top, t_token *new)
{
	t_token	*token_ptr;

	if (!*token_top)
	{
		*token_top = new;
		return ;
	}
	token_ptr = *token_top;
	while (token_ptr->next)
		token_ptr = token_ptr->next;
	token_ptr->next = new;
}

int	has_unclosed_quote(char *input)
{
	char	quote;
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}

void	tokens_free(t_token *token_top)
{
	t_token	*token_ptr;

	while (token_top)
	{
		token_ptr = token_top->next;
		free(token_top->value);
		free(token_top);
		token_top = token_ptr;
	}
}
