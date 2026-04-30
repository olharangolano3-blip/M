/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <adjigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:29:36 by adjigo            #+#    #+#             */
/*   Updated: 2026/04/30 09:35:43 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			g_signal = 0;

void	handle_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	process_line(char *line, t_shell *shell)
{
	t_token		*tokens;
	t_pipeline	*pipeline;

	if (!*line)
		return ;
	tokens = tokenize(line);
	if (!tokens)
		return ;
	if (validate_syntax(tokens) == -1)
	{
		tokens_free(tokens);
		shell->exit_status = 2;
		return ;
	}
	pipeline = parse(tokens, shell);
	tokens_free(tokens);
	if (!pipeline)
	{
		if(g_signal == SIGINT)
			shell->exit_status = 130;
		return ;	
	}
	if (expand(pipeline, shell) == -1)
	{
		pipeline_free(pipeline);
		return ;
	}
	execute(pipeline, shell);
	pipeline_free(pipeline);
}

static void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		g_signal = 0;
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			return ;
		}
		add_history(line);
		if (has_unclosed_quote(line))
		{
			ft_putstr_fd("minishell: syntax error, unclosed quote\n", 2);
			shell->exit_status = 2;
		}
		else
			process_line(line, shell);
		free(line);
		if (shell->should_exit)
			return ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.env = env_copy(envp);
	shell.exit_status = 0;
	shell.should_exit = 0;
	if (!shell.env)
		return (1);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	shell_loop(&shell);
	env_free(shell.env);
	return (shell.exit_status);
}
