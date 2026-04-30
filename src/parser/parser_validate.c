/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:00:00 by dalde-ol          #+#    #+#             */
/*   Updated: 2026/04/26 12:00:00 by dalde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (-1);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*t;

	t = tokens;
	if (!t)
		return (0);
	if (t->type == TOKEN_PIPE)
		return (syntax_error("|"));
	while (t)
	{
		if (t->type == TOKEN_PIPE)
		{
			if (!t->next || t->next->type == TOKEN_PIPE)
				return (syntax_error("|"));
		}
		if (t->type == TOKEN_REDIR_IN || t->type == TOKEN_REDIR_OUT
			|| t->type == TOKEN_REDIR_APPEND || t->type == TOKEN_HEREDOC)
		{
			if (!t->next || t->next->type != TOKEN_WORD)
				return (syntax_error("newline"));
			t = t->next;
		}
		t = t->next;
	}
	return (0);
}
