#include "minishell.h"

void print_tokens(t_token *tokens, t_mini *mini)
{
    t_token *current_token;
    int i;

    i = 0;
    while (mini->splited[i] != NULL)
    {
        printf("Splited[%d]: %s\n", i, mini->splited[i]);
        i++;
    }
    i = 0;
    current_token = tokens;
    while (current_token != NULL)
    {
        printf("Token %d: text:%s type:%d\n", i, current_token->text, current_token->type);
		if(current_token->prev)
			ft_printf("prev->text: %s\n\n", current_token->prev->text);
		else
			ft_printf("\n");
        current_token = current_token->next;
        i++;
    }
	ft_printf("\n");
}

/**
 * @brief on a loop, will handle the readlines, parse, do the executor and free everything
 * 
 * @param mini the struct
 * @param token the list of tokens
 */
static void minishell(t_mini *mini, t_token	**token, char **envp)
{
	char *rl;
	
	rl = NULL;
	while(1)
	{
		ft_signals();
		rl = readline("miniShell: ");
		if (!rl)
            handle_eof(token, mini);
		mini->line = rl;
		if (mini->line[0])
            split_to_tokens(mini->line, mini);
		if(!mini->splited)
			continue;
		if(!parse(mini, token, envp))	
		{
			free_things(mini);
			freethem(token, mini);
			continue;
		}
		print_tokens(*token, mini);
		add_history(mini->line);
		executor(token, mini);
		freethem(token, mini);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_mini mini;
	t_token *token;
	(void)argc;
	(void)argv;
	
	token = NULL;
	ft_memset(&mini, 0, sizeof(t_mini));
	minishell(&mini, &token, envp);
}
