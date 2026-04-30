/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjigo <adjigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:38:10 by dalde-ol          #+#    #+#             */
/*   Updated: 2026/04/30 11:03:09 by adjigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

extern int			g_signal;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_REDIR_IN,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				heredoc_fd;
	int				expand;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	int				argc;
	t_redir			*redirs;
	char			*cmd_path;
	bool			is_builtin;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pipeline
{
	t_cmd			*cmds;
	int				count;
}					t_pipeline;

typedef struct s_shell
{
	char			**env;
	int				exit_status;
	int				should_exit;
}					t_shell;

typedef struct s_exec_ctx
{
	int				pipe_idx;
	int				pipe_count;
	int				(*pipes)[2];
	t_pipeline		*pipeline;
}					t_exec_ctx;

typedef struct s_parse_ctx
{
    t_token			*tokens;
    t_pipeline		*pipeline;
    t_cmd			*cmd;
}					t_parse_ctx;

void				handle_sigint(int sig);

/* STEP 1 — TOKENIZER */
t_token				*tokenize(char *input);
t_token				*token_new(t_token_type type, char *value);
void				token_add_back(t_token **token_top, t_token *new);
int					has_unclosed_quote(char *input);
void				tokens_free(t_token *token_top);

/* STEP 2 — PARSER */
t_pipeline			*parse(t_token *tokens, t_shell *shell);
t_pipeline			*pipeline_new(void);
t_cmd				*cmd_new(void);
t_redir				*redir_new(t_token_type type, char *file);
void				cmd_add_redir(t_cmd *cmd, t_redir *redir);
void				pipeline_add_cmd(t_pipeline *pipeline, t_cmd *cmd);
int					cmd_add_argv(t_cmd *cmd, char *value);
void				pipeline_free(t_pipeline *pipeline);
void				cmd_free(t_cmd *cmd);
int					validate_syntax(t_token *tokens);
int					heredoc_read(t_redir *redir, t_shell *shell, t_parse_ctx *ctx);
void				pipeline_print(t_pipeline *pipeline);
char				*get_segment(char *word, int *i, t_shell *shell);
char				*get_single(char *word, int *i);

/* STEP 3 — EXPANDER */
int					expand(t_pipeline *pipeline, t_shell *shell);
char				*expand_word(char *word, t_shell *shell);
char				*get_var_value(const char *str, int *i, t_shell *shell);
char				*append_segment(char *result, char *val);
char				*process_double_quote(const char *str, int *i,
						t_shell *shell);
char				*process_unquoted(const char *str, int *i,
						t_shell *shell);
/* STEP 4 — ENV UTILS */
int					env_add(t_shell *shell, const char *entry);
int					env_export_name(t_shell *shell, const char *name);
int					env_count(char **envp);
char				**env_copy(char **envp);
char				*env_get(char **env, const char *name);
int					env_set(t_shell *shell, const char *name, const char *val);
int					env_unset(t_shell *shell, const char *name);
void				env_free(char **env);

/* STEP 5 — EXECUTOR */
char				*resolve_path(char *cmd, char **env);
char				*free_dirs_return(char **dirs, char *full);
int					apply_redirections(t_redir *redirs);
int					setup_pipes(int pipe_count, int pipes[][2]);
void				close_pipes(int pipe_count, int pipes[][2]);
void				child_exit(t_shell *shell, t_pipeline *pipeline, int code);
void				init_ctx(t_exec_ctx *ctx, t_pipeline *pipeline,
						int pipe_count, int pipes[][2]);
int					wait_children(pid_t *pids, int count);
int					fork_pipeline(t_pipeline *pipeline, t_shell *shell,
						int pipe_count, int pipes[][2]);
int					execute(t_pipeline *pipeline, t_shell *shell);

/* STEP 6 — BUILTINS */
int					is_builtin(char *cmd);
int					run_builtin(t_cmd *cmd, t_shell *shell);
int					builtin_echo(t_cmd *cmd);
int					builtin_cd(t_cmd *cmd, t_shell *shell);
int					builtin_pwd(t_cmd *cmd);
int					builtin_export(t_cmd *cmd, t_shell *shell);
int					builtin_unset(t_cmd *cmd, t_shell *shell);
int					builtin_env(t_cmd *cmd, t_shell *shell);
int					builtin_exit(t_cmd *cmd, t_shell *shell);

#endif
