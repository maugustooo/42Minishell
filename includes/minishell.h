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
# define MAX_PATH_LEN 4096

# define CMD_PATH "/bin/"
# define HOME "/home/$USER"

typedef enum e_error
{
	ERROR_CMD,
	ERROR_CD,
	ERROR_EXPORT,
	ERROR_PIPE,
	ERROR_ARG_ECHO,
	ERROR_ENV
}	t_error;

// const char *Error_Msg[] =
// {
//     [ERROR_CMD] = "%s: command not found",
//     /* etc. */  
// };

static inline const char *Error_Msg(enum e_error i)
{
    static const char *strings[] = { "%s: command not found\n",
	"minishell: cd: %s: No such file or directory",
	"minishell: export: `%s': not a valid identifier\n",
	"syntax error\n", "parse error near '%s'\n"/* continue for rest of values */ };
    return strings[i];
}

typedef struct s_token
{
	char			*text;	
	int				type;
	struct s_token	*next;
} t_token;



typedef struct s_mini
{
	char	*line;
	char	**penv;
	char	*prev_dir;
	char	**splited;

	bool	echo_flag;
	bool	pipe;
	bool	final_pipe;

	int		token_count;
	int		return_code;
} t_mini;

//--------------Utils-------------//

t_token	*ft_tokenlast(t_token *token);
void	ft_tokenadd_back(t_token **token, t_token *new_token);
t_token	*ft_newnode(int type, char *text);
void	ft_tokenclear(t_token **token);
void	ft_tokendelone(t_token *token);
void	freethem(t_token **token, t_mini *mini);
void	free_things(t_mini *mini);
int		env_size(t_mini *mini, char **tenv);
void	free_tenv(char **tenv);
void	free_penv(t_mini *mini);
void	free_key(char **key);
void	dup_envp(t_mini *mini, char **envp);
void	dup_tenv(t_mini *mini, char **tenv);
char	*get_env_key(t_mini *mini, char *str);
char	*get_env_value(t_mini *mini, char *str);
void	handle_quotes(char c, int *in_quotes, char *quote_char);
void	print_tokens(t_token *tokens, t_mini *mini);
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
void	expand_input(t_token *token, t_mini *mini, char **input);
void	handle_not_sq(t_token **token,t_mini *mini,  int *i);
void	change_quotes(t_token **token);
void	handle_expansion(t_token **token, t_mini *mini);
char	*handle_sign2(t_token **token, t_mini *mini, int *i, int *len);
char	*handle_dq2(t_token **token, t_mini *mini, int *i, int *start,char *segment);
char	*handle_sign(t_token **token, t_mini *mini, int *i, int *start);

//------------Executor-----------//
void	pipes(t_token **token, t_mini *mini, int pid);
void	handle_cd(t_token *arg, t_mini *mini);
void	handle_exit(t_token **token, t_mini *mini);
void	handle_echo(t_token *next, t_mini *mini);
void	handle_env(t_mini *mini, t_token *next);
void	handle_pwd(t_mini *mini);
void	set_export(t_mini *mini, t_token *token);
void	handle_export(t_mini *mini, t_token *token);
void	handle_unset(t_token *token, t_mini *mini);
void	executor(t_token **token, t_mini *mini);
#endif