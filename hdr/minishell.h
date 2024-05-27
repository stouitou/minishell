/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:06:18 by stouitou          #+#    #+#             */
/*   Updated: 2024/05/27 16:49:07 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/hdr/libft.h"
# include "../Libft/hdr/ft_printf.h"
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# ifndef PROMPT
#  define PROMPT "\033[32mminishell > \033[0m"
# endif

# ifndef H_PROMPT
#  define H_PROMPT "> "
# endif

# ifndef H_FILE
#  define H_FILE "heredoc"
# endif

# ifndef METACHARACTER
#  define METACHARACTER " \t\n\v|<>"
# endif

# ifndef ERR_QUOTES
#  define ERR_QUOTES "unexpected EOF while looking for matching"
# endif

# ifndef ERR_MALLOC
#  define ERR_MALLOC "Error allocating memory"
# endif

# ifndef ERR_ISDIR
#  define ERR_ISDIR "Is a directory"
# endif

# ifndef ERR_SYNTAX
#  define ERR_SYNTAX "syntax error near unexpected token"
# endif

# ifndef ERR_CMD
#  define ERR_CMD "command not found"
# endif

# ifndef ERR_PERM
#  define ERR_PERM "permission denied"
# endif

enum	e_quotes
{
	UNQUOTED,
	SIMPLE,
	DOUBLE,
};

enum	e_type
{
	WORD,
	OPERATOR,
};

enum	e_cat
{
	CMD = 1,
	INFILE = 2,
	OUTFILE = 3,
	DELIMITER = 4,
	APP_OUTFILE = 5,
	OPTION = 6,
	ARG = 7,
	CTL_OP = 11,
	REDIR_OP = 12,
};

typedef struct s_token
{
	char			*content;
	int				index;
	int				quotes;
	int				block;
	int				type;
	int				category;
	struct s_token	*head;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_error
{
	char	*msg;
	char	*data;
	int		status;
}			t_error;

typedef struct s_files
{
	char			*content;
	int				category;
	struct s_files	*next;
}					t_files;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_exe
{
	t_env		*env;
	int			blocks;
	int			pipe_fd1[2];
	int			pipe_fd2[2];
	pid_t		subshell;
	t_files		*files;
	char		*delimiter;
	int			io_fd[2];
	char		**cmd;
	t_error		error;
}				t_exe;


typedef struct s_entry
{
	char	*str;
	t_token *token;
	bool	heredoc;
	int		prev_status;
	int		status;
	bool	exit;
	char	**env;
}			t_entry;

int			main(int ac, char **av, char **env);
void		stash_str(t_entry *entry, t_token **token, char *str);
void		handle_metachars(t_entry *entry, t_token *new, int *i, int *ib);
void		handle_non_metachars(t_entry *entry, t_token *new, char *str, int *i);
void		analyze_syntax(t_entry *entry);
void		handle_expansions(t_entry *entry, char **env);
void		expand_token(t_entry *entry, t_token *token, char **env);
void		classify_tokens(t_entry *entry);
void		go_heredoc(t_entry *entry, t_token *cur);
void		gather_indexes(t_entry *entry, t_token *cur);
void		exec_token(t_entry *entry, t_token *token);
void		set_env(t_entry *entry, t_exe *exe);
void		find_files(t_entry *entry, t_exe *exe, t_token *token);
void		exec_subshell(t_exe *exe, int i, int prev_status);
char		*find_cmd(t_exe *exe, char **cmd);

/* BUILTIN */
bool		is_builtin(char *command);
int			handle_exit_in_parent(t_entry *entry, t_exe *exe, char **cmd);
int			handle_export_in_parent(t_entry *entry, t_exe *exe, t_env *env, char **cmd);
void		handle_builtin(t_exe *exe, char *command, int prev_status);
void		handle_echo(t_exe *exe, char **cmd);
void		handle_export(t_exe *exe, char **cmd, t_env *env);
void		export_only(t_exe *exe, t_env *env);
void		handle_exit(t_exe *exe, char **cmd, int prev_status);
int			get_files_fd_for_exit(t_exe *exe, t_files *file);
void		handle_env(char **cmd, t_env *env);

/* LIST */
t_token		*token_new(int *ib);
void		token_addback(t_token **token, t_token *new);
void		token_clear(t_token **token);
void		del_node(t_token **node);
t_files		*files_new(t_entry *entry, t_exe *exe, t_token *token);
void		files_addback(t_files **file, t_files *new);
void		files_clear(t_files **file);
t_env		*env_new(char *key, char *value);
void		env_addback(t_env **env, t_env *new);
int			env_size(t_env *env);
void		env_clear(t_env **env);

/* INIT */
void		init_exe(t_entry *entry, t_token *token, t_exe *exe, int i);
void		init_pipe(t_entry *entry, t_exe *exe, int *pipe_fd);
pid_t		init_fork(t_exe *exe, t_entry *entry);
void		init_dup(t_exe *exe, int old_fd, int new_fd);
void		init_error(t_exe *exe, char *msg, char *data, int status);

/* UTILS */
void		skip_whitespace(char *str, int *index);
void		close_both_fd(int fd1, int fd2);
void		close_all_fd(t_exe *exe);
void		remove_node(t_token **token, t_token *cur);
void		upd_token_heads_and_indexes(t_token *token);
char		**upd_env(t_exe *exe, t_env *env);
void		free_4_str(char *str1, char *str2, char *str3, char *str4);

/* FREE */
void		free_token_and_exit(t_entry *entry, char *err, char *str, int status);
void		free_token_before_return(t_entry *entry, char *err, char *str, int error);
void		free_exe(t_exe *exe);
void		free_cmd(char **cmd);
void		free_subshell_and_exit(t_exe *exe);
void		exit_builtin(t_exe *exe, char *builtin);

/* PRINT */
void		print_tab(char **env);
void		print_env(t_env *env);
void		print_full_command(t_entry *entry, t_token *token);
void		print_token(t_entry *entry, t_token *token);
void		print_block(t_token *token);
void		print_exe(t_entry *entry, t_token *token, t_exe *exe, int block);
int			print_utils_token_size(t_token *token);
int			print_utils_token_blocks(t_token *token);
int			print_utils_content_has_space(char *content);

/* TESTER */
void		log_tests(const char *command);
void		log_status(int status);

#endif
