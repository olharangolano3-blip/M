/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:24:08 by dalde-ol          #+#    #+#             */
/*   Updated: 2026/04/20 12:00:00 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	extract_operator(char *input, int i, t_token **token_top)
{
	t_token	*new;
	int		advance;

	advance = 1;
	if (input[i] == '|')
		new = token_new(TOKEN_PIPE, "|");
	else if (input[i] == '>' && input[i + 1] == '>')
	{
		new = token_new(TOKEN_REDIR_APPEND, ">>");
		advance = 2;
	}
	else if (input[i] == '>')
		new = token_new(TOKEN_REDIR_OUT, ">");
	else if (input[i] == '<' && input[i + 1] == '<')
	{
		new = token_new(TOKEN_HEREDOC, "<<");
		advance = 2;
	}
	else
		new = token_new(TOKEN_REDIR_IN, "<");
	if (!new)
		return (-1);
	token_add_back(token_top, new);
	return (i + advance);
}

static int	skip_quoted(char *input, int i)
{
	char	quote;

	quote = input[i];
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
		i++;
	return (i);
}

static int	extract_word(char *input, int i, t_token **token_top)
{
	int		start;
	char	*value;
	t_token	*new;

	start = i;
	while (input[i] && input[i] != ' ' && input[i] != '\t'
		&& input[i] != '|' && input[i] != '<' && input[i] != '>')
	{
		if (input[i] == '\'' || input[i] == '"')
			i = skip_quoted(input, i);
		else
			i++;
	}
	value = ft_substr(input, start, i - start);
	if (!value)
		return (-1);
	new = token_new(TOKEN_WORD, value);
	free(value);
	if (!new)
		return (-1);
	token_add_back(token_top, new);
	return (i);
}

t_token	*tokenize(char *input)
{
	t_token	*token_top;
	int		i;

	token_top = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i = extract_operator(input, i, &token_top);
		else
			i = extract_word(input, i, &token_top);
		if (i == -1)
		{
			tokens_free(token_top);
			return (NULL);
		}
	}
	return (token_top);
}
