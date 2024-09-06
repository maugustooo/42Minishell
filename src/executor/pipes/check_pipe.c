# include "minishell.h"

void check_pipes(int *is_pipe, t_token **temp)
{
	*is_pipe = ((*temp)->next && strcmp((*temp)->next->text, "|") == 0);
	while ((*temp)->next && !*is_pipe)
	{
		*temp = (*temp)->next;
		*is_pipe = ((*temp)->next && strcmp((*temp)->next->text, "|") == 0);
	}
}
