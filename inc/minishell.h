/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:37:12 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/23 12:13:03 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <libft.h>
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>

/* |~~~ FILE DESCRIPTORS ~~~| */
# define STDIN 0
# define STDOUT 1
# define STDERR 2

/* |~~~ ERROR CODES ~~~| */
# define MALLOC_ERROR 33
# define PARSE_ERROR 34
# define QUOTE_REMOVE_ERROR 35
# define HEREDOC_ERROR 36

/* |~~~ ERROR MESSAGES ~~~| */
# define ERROR_FORK "minishell: fork error\n"
# define ERROR_MALLOC "minishell: malloc error\n"
# define ERROR_PIPE "minishell: pipe error\n"
# define ERROR_PWD "minishell: pwd error\n"
# define ERROR_CD "minishell: cd: "
# define ERROR_EXPORT "minishell: export: "
# define ERROR_UNSET "minishell: unset failed\n"
# define ERROR_EXPORT_WRITE "minishell: export: error writing to environment\n"
# define ERROR_EXPORT_READ "minishell: export: error reading environment\n"

/* |~~~ PARSER STATUS ~~~| */
# define SYNTAX 258

/* |~~~ PARSER ERROR MSG ~~~| */
# define PIPE_TO_NOTHING "minishell: syntax error no command after pipe"
# define NO_CLOSING_QUOTE "minishell: syntax error closing quote not found"
# define PIPE_NEAR "minishell: syntax error near unexpected token `|'"
# define NEWLINE_NEAR "minishell: syntax error near unexpected token `newline'"
# define HEREDOC_NEAR "minishell: syntax error near unexpected token `<<'"
# define APPEND_NEAR "minishell: syntax error near unexpected token `>>'"
# define INPUT_NEAR "minishell: syntax error near unexpected token `<'"
# define OUTPUT_NEAR "minishell: syntax error near unexpected token `>'"

/* |~~~ PROMPT ~~~| */
# define PROMPT "\001\e[38;5;118m\002MI\001\e[38;5;154m\002NI\001\e[38;5;148m\
\002SHE\001\e[38;5;184m\002LL$\001\e[38;5;231m\002\033[0m\001 "
# define HEREDOC_PROMPT "\e[38;5;118m>\e[38;5;231m\033[0m "

/* |~~~ LEXER TYPES ~~~| */
# define OTHERS 0
# define WORD 1
# define VARIABLE 36
# define ARGUMENT 45
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define IN_BRACKET 60
# define OUT_BRACKET 62
# define UNDERSCORE 95
# define PIPE 124 
# define ANGLE_BRACKETS 6062

/* |~~~ TOKEN TYPES ~~~| */
# define TYPE_CMD 1
# define TYPE_ARG 2
# define TYPE_VAR 36
# define TYPE_INPUT 60
# define TYPE_OUTPUT 62
# define TYPE_PIPE 124
# define TYPE_NEWLINE 202
# define TYPE_HEREDOC 6060
# define TYPE_APPEND 6262
# define TYPE_OTHERS 666666666

/* |~~~ CMD TYPE ~~~| */
# define CMD_NOT_BUILT_IN 1
# define CMD_BUILT_IN 2
# define CMD_HEREDOC 3
# define CMD_APPEND 4
# define CMD_INPUT 5
# define CMD_OUTPUT 6
# define CMD_PIPE 7

/* |~~~ EXECUTION POSITION ~~~| */
# define START 0

/* |~~~ SIGNAL STRUCT ~~~| */
typedef struct s_status
{
	int	exit_status;
	int	cmd_execution;
	int	cd_status;
	int	file_is_folder;
	int	infile_problem;
	int	eof;
	int	sigint;
	int	in_heredoc;
	int	heredoc_fd[2];
}	t_status;

/* |~~~ TOKEN STRUCT ~~~| */
typedef struct s_token
{
	int				type;
	char			*data;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/* |~~~ CMD STRUCT ~~~| */
typedef struct s_cmd
{
	int		infile;
	int		outfile;
	int		problem_with_file;
	int		can_remove_quotes;
	char	*cmd;
	char	*raw_cmd;
	char	*raw_with_var;
	char	*cmd_path;
	char	**args;
	char	**raw_args;
	char	*heredoc;
	char	*heredoc_filename;
	int		type;
}	t_cmd;

/* |~~~ SHELL STRUCT ~~~| */
typedef struct s_shell
{
	int		new_fds[2];
	int		old_fds[2];
	int		shell_size;
	int		parser_status;
	int		*pid;
	char	*buffer;
	char	**env;
	char	*home_dir;
	char	*minishell_env_dir;
	char	*minishell_heredoc_dir;
	size_t	pipe_count;
	size_t	cmd_count;
	size_t	redir_count;
	size_t	heredoc_count;
	size_t	cmd_list_size;
	t_cmd	*cmd;
	t_token	*tokens;
}	t_shell;

/* |~~~ GLOBAL VARIABLE ~~~| */
extern t_status	g_status;

/* |~~~ PROTOTYPES ~~~| */
int				ft_type(char c);
int				ft_env(char **env);
int				ft_is_empty(char *arg);
int				ft_ctrl_d_heredoc(void);
int				ft_not_closed(char *str);
int				ft_has_quotes(char *str);
int				ft_is_lowercase(char *str);
int				ft_has_input(char *buffer);
int				ft_has_variable(char *cmd);
int				ft_is_special_space(char *str);
int				ft_has_plus_simbol(char *str);
int				ft_max_or_min_nbr(char *str);
int				ft_is_not_arg(t_token *tokens);
int				ft_begin_with_space(char *str);
int				ft_not_inside_quotes(char *str);
int				ft_get_opposite(int type);
int				ft_is_empty_with_quotes(char *arg);
int				ft_execute(t_shell *shell, t_cmd *cmd);
int				ft_last_repeated(char **args, size_t id);
int				ft_is_a_folder(char *path, t_cmd *cmd);
int				ft_space_alone(char *buffer, size_t pos);
int				ft_is_valid_export(char **args, size_t id);
int				ft_valid_to_remove_quotes(t_cmd *cmd);
int				ft_parser(t_shell *shell, t_token **tokens);
int				ft_clean_argument(t_cmd *cmd, size_t pos);
int				ft_heredoc_reader(t_cmd *cmd, char *delimiter);
int				ft_parser_error(t_shell *shell, int status, int type);
int				ft_open_file(t_cmd *cmd, char *filename, int type);
int				ft_remove_args_quotes(t_shell *shell, t_cmd *cmd);
int				ft_remove_cmd_quotes(t_shell *shell, t_cmd *cmd);
int				ft_has_syntax_error(t_shell *shell, t_token **tokens);
int				ft_redirection_error(t_shell *shell, t_token *token, int type);
int				ft_more_redir_error(t_shell *shell, t_token *token, int type);
int				ft_remove_quotes_valid(char *cmd, int can_remove_quotes,
					int type);

size_t			ft_varlen(char *var);
size_t			ft_arrlen(char **arr);
size_t			ft_file_size(char *filename);
size_t			ft_atoul(const char *string);
size_t			ft_len_no_spaces(char *str);
size_t			ft_strlen_x(char *str, char limit);
size_t			ft_count_cmds(t_token **tokens);
size_t			ft_count_heredoc(t_token **tokens);
size_t			ft_out_of_quotes(char *buffer, int type);
size_t			ft_count_redirections(t_token **tokens);
size_t			ft_need_expansion(char *raw, char *clean);
size_t			ft_size_without_quotes(char *str, int mode);
size_t			ft_strllen(char *str, char limit, int mode, size_t stop);

char			*ft_to_lower(char *str);
char			ft_first_quote(char *str);
char			**ft_copy_env(char **env);
char			**ft_read_env(t_shell *shell);
char			*ft_get_path(char **env, char *cmd);
char			**ft_write_env(t_shell *shell, char **env);
char			*ft_remove_char(char *str, char remove);
char			*ft_get_var_values(char **env, char *var);
char			*ft_get_with_space(char *dest, char *cmd);
char			*ft_find_var(char **env, char *arg, size_t len);
char			**ft_add_args(t_cmd *cmd, char **add_args);
char			*ft_joinstr(char *start, char *mid, size_t stop);
char			*ft_get_value(char **env, char *var, int mode);
char			*ft_get_var(char **env, char *var, size_t count);
char			**ft_get_raw_args(char *path, t_token *tokens);
char			*ft_remove_interrogation(char *var, char *value);
char			**ft_get_args(char *path, char **env, t_token *tokens);
char			*ft_parse_cmd(t_cmd *cmd, char **env, char *command);
char			*ft_remove_quotes(char *str, size_t size, char *first_quote);
char			**ft_remove_and_append(t_shell *shell, char **args,
					size_t valid_args);
char			**ft_heredoc_to_file(t_shell *shell, t_cmd *cmd, char *heredoc,
					size_t count);

void			ft_pwd(char **args);
void			ft_printstr(char *str);
void			ft_ctrl_d(t_shell *shell);
void			ft_handle_signals(void);
void			ft_free_array(char **arr);
void			ft_export_error(char *arg);
void			ft_ctrl_c_heredoc(int signal);
void			ft_destroy_shell(t_shell *shell);
void			ft_clean_heredoc(t_cmd *cmd);
void			ft_cd(t_shell *shell, char **args);
void			*ft_print_error(char *error_msg);
void			*ft_command_line(t_shell *shell);
void			*ft_free_tokens(t_token **tokens);
void			*ft_free_everything(t_shell *shell);
void			ft_unset(t_shell *shell, char **args);
void			ft_export(t_shell *shell, char **args);
void			*ft_append(char *heredoc, char *line);
void			ft_command_not_found(t_cmd *cmd);
void			ft_export_without_args(t_shell *shell);
void			ft_wrong_exit_argument(t_cmd *cmd);
void			*ft_heredoc(t_shell *shell, t_cmd *cmd);
void			ft_exit_and_free(int exit_status, t_shell *shell);
void			ft_exit(t_shell *shell, t_cmd *cmd, char **args);
void			*ft_get_commands(t_shell *shell, t_token **tokens);
void			ft_built_in_out(t_shell *shell, t_cmd *cmd, char **args);
void			ft_handle_fds(t_shell *shell, t_cmd *cmd, size_t position);
void			ft_reset_quote_counts(size_t *quote_count, int *opposite);
void			*ft_get_heredoc(t_cmd *cmd, size_t count, char *first_quote);
void			ft_echo(t_cmd *cmd, char *raw_cmd, char *cmd_path, char **arg);
void			ft_exec_built_in(t_shell *shell, t_cmd *cmd, char **args,
					char **env);

t_token			*ft_last_token(t_token *tokens);
t_token			*ft_lexer(char *buffer, t_shell *shell);
t_token			*ft_create_token(t_token **tokens, char *data, t_shell *shell);

t_cmd			*ft_expand_args(t_cmd *cmd);
t_cmd			*ft_expand_cmd(t_shell *shell, t_cmd *cmd);
t_cmd			*ft_cmd_expansion(t_shell *shell, t_cmd *cmd);
t_cmd			*ft_redir_expansion(t_shell *shell, t_cmd *cmd);
t_cmd			*ft_redistribute_cmds(t_shell *shell, t_cmd *cmd);
t_cmd			*ft_expand_args_with_var(t_shell *shell, t_cmd *cmd);
t_cmd			*ft_expand_cmd_with_var(t_shell *shell, t_cmd *cmd);

pid_t			*ft_process(t_shell *shell, t_cmd *cmd, pid_t *pid);
pid_t			ft_process_cmd(t_shell *shell, t_cmd *cmd, size_t pos);
pid_t			ft_process_redir(t_shell *shell, t_cmd *cmd, size_t pos);
pid_t			ft_process_built_in(t_shell *shell, t_cmd *cmd, size_t pos);

#endif
