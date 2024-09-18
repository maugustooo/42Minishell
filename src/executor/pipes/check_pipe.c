# include "minishell.h"

void check_pipes(t_mini *mini, t_token **temp)
{
	mini->is_pipe = ((*temp)->next && strcmp((*temp)->next->text, "|") == 0);
	while ((*temp)->next && !mini->is_pipe)
	{
		*temp = (*temp)->next;
		mini->is_pipe = ((*temp)->next && strcmp((*temp)->next->text, "|") == 0);
	}
}
