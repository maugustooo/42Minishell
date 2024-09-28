#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define CMD 1
# define ARG 2
# define INPUT 3
# define OUTPUT 4
# define DELIMITER 5
# define APPEND 6
# define PIPE 7
# define FILE 8
# define NOT_FILE 9
# define MAX_PATH_LEN 4096

# define CMD_PATH "/bin/"
# define HOME "/home/$USER"
# define TEMP_FILE "/tmp/minishell_heredoc.txt"

typedef enum e_error
{
	ERROR_CMD,
	ERROR_CD,
	ERROR_EXPORT,
	ERROR_PIPE,
	ERROR_ARG_ECHO,
	ERROR_ENV,
	ERROR_TARG,
	ERROR_NUMARG,
	ERROR_ISDIR,
	ERROR_PERMS,
	ERROR_SENV,
	ERROR_NDIR,
	ERROR_NFILE,
	ERROR_ENUM
}	t_error;

static inline const char *Error_Msg(enum e_error i)
{
    static const char *strings[] = { 
	"%s: command not found\n",
	"minishell: cd: %s: No such file or directory\n",
	"minishell: export: `%s': not a valid identifier\n",
	"Syntax error near '%s'\n",
	"ARG ECHO ERROR\n",
	"ERROR NO ENV\n",
	"minishell: %s: too many arguments\n",
	"minishell: %s: numeric argument required\n",
	"minishell: %s: Is a directory\n",
	"minishell: %s: Permission denied\n",
	"env: Options/Arguments not allowed by subject\n",
	"minishell: cd: %s: Not a directory\n",
	"minishell: %s: No such file or directory\n",
	"minishell: exit: %s: numeric argument required",};
    return strings[i];
}

typedef struct s_token
{
	char			*text;	
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;



typedef struct s_mini
{
	char	*line;
	char	**penv;
	char	*prev_dir;
	char	**splited;
	char	curr_dir[MAX_PATH_LEN];

	bool	echo_flag;
	bool	pipe;
	bool	final_pipe;
	bool	exported;

	int		is_pipe;
	int		token_count;
	int		return_code;
	int		num_pipes;
	int		redirect;
	int		moved;

	int		input;
	int		input_count;
	int		output_count;
	int		append_count;
	int		file_count;
} t_mini;

//--------------Utils-------------//

t_token	*ft_tokenlast(t_token *token);
t_token	*ft_tokenlast_redirect(t_token *token);
t_token	*ft_newnode(int type, char *text);
void	ft_tokenadd_back(t_token **token, t_token *new_token);
void	ft_tokenclear(t_token **token);
void	ft_tokendelone(t_token *token);
int		count_nodes(t_token *token);
void	freethem(t_token **token, t_mini *mini);
void	free_things(t_mini *mini);
int		env_size(t_mini *mini, char **tenv);
void	free_tenv(char **tenv);
void	free_penv(t_mini *mini);
void	free_key(char **key);
void	free_args(char **args);
void	free_keys(char ***key);
void	dup_envp(t_mini *mini, char **envp);
void	dup_tenv(t_mini *mini, char **tenv);
void	move_left(char **args, int start_index);
char	*get_env_key(t_mini *mini, char *str);
char	*get_env_value(t_mini *mini, char *str);
void	handle_quotes(char c, int *in_quotes, char *quote_char);
void	print_tokens(t_token *tokens, t_mini *mini);
void	free_child(t_token **token, t_mini *mini, char **args);
int		check_file_token(t_token **token, char *file, t_mini *mini);
int		check_redirect(t_token **next);
int		check_dir(char *tgt_dir);
int		export_arg_err(t_token *token, t_mini *mini, char **key);
void	check_export_expander(t_token *token, t_mini *mini);
void	error_malloc(t_mini *mini);
void	handle_exit_conditions(const char *msg, t_token **token, t_mini *mini, char **args);
void	count_redirections(t_token *token, t_mini *mini);
int		check_file_perms(t_token *token);
int		check_file_red(char *file);
char	**change_args_exec(char **args, t_token *token, t_mini *mini);
//--------------Parser------------//

int		parse(t_mini *mini, t_token	**token, char **envp);
void	get_tokens(t_token	**token, t_mini *mini);
void	ft_signals(void);
void	handle_eof(t_token **token, t_mini *mini);
void	split_to_tokens(char *line, t_mini *mini);
int		count_tokens(char *line, t_mini *mini);

//------------Expander-----------//

void	expander(t_token **token, t_mini *mini);
void	change_token_text(t_token *token, char *value);
void	change_quotes(t_token **token);
void	handle_expansion(t_token **token, t_mini *mini);
char	*handle_sign2(t_token **token, t_mini *mini, int *i, int *len);
char	*handle_dq2(t_token **token, t_mini *mini, int *i, int *start, char *segment);
char	*handle_sign(t_token **token, t_mini *mini, int *i, int *start);

//------------Executor-----------//

int		is_built_in(t_token *token);
void	handle_built_ins(t_token **token, t_mini *mini);
void	pipes(t_token **token, t_mini *mini);
void	check_pipes(t_mini *mini, t_token **temp);
void	handle_cd(t_token *arg, t_mini *mini);
void	handle_exit(t_token **token, t_mini *mini);
void	handle_echo(t_token **token, t_mini *mini);
void	handle_env(t_mini *mini, t_token *toke);
void	handle_pwd(t_mini *mini);
void	set_export(t_mini *mini, t_token *token);
void	handle_export(t_mini *mini, t_token *token);
int		export_arg(t_token *token, t_mini *mini);
void	check_arg_export(t_token *token, t_mini *mini);
void	handle_unset(t_token *token, t_mini *mini);
void	executor(t_token **token, t_mini *mini);

//------------Commands-----------//

char	*build_full_path(char *dir, const char *cmd, t_mini *mini);
int		check_access(char *full_path);
int		handle_cmd(t_token **token, t_mini *mini);
int		handle_cmd_pipe(t_token **token, t_mini *mini);
int		handle_cmd2(t_token **token, t_mini *mini, char **args);
int		handle_cmd3(t_token **token, t_mini *mini, char **args);
int		handle_cmd3_5(t_token *temp, t_token **token, t_mini *mini, char **args);
int		check_command(t_token **token, t_mini *mini, char **args);
int		check_command2(char *full_path, char **dirs, t_token **token, t_mini *mini);
int		check_file(char **argv, t_token **token, t_mini *mini);
int		check_file2(char **args, t_token **token, t_mini *mini);
int		check_path(t_mini *mini);
void	handle_heredoc(char ***args, int *i, t_mini *mini);
int		handle_input(char ***args, int	*i, t_mini *mini);
int		handle_output(char ***args, int	*i, t_mini *mini);
void	handle_redirection(char **args, t_mini *mini,  t_token **token);
#endif