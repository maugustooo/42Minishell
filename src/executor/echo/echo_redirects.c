#include "minishell.h"

int check_redirect(t_token **next)
{
	int len;

	len = 0;
	if ((*next)->type == OUTPUT || (*next)->type == FILE ||(*next)->type == NOT_FILE)
		{
			if((*next)->type == FILE || (*next)->type == NOT_FILE)
			{
				if((*next)->type == NOT_FILE)
					return(2);
				(*next) = (*next)->next;
				return (1);
			}
			len = ft_strlen((*next)->text);
			if((*next)->type == OUTPUT && ((*next)->text[0] != '"' && (*next)->text[len -1] != '"') && ((*next)->text[0] != '\'' && (*next)->text[len -1] != '\''))
			{
				(*next) = (*next)->next;	
				return (1);
			}
			if(((*next)->text[1] == '"' && (*next)->text[len -1] == '"') || ((*next)->text[1] == '\'' && (*next)->text[len -1] == '\''))
			{
				(*next) = (*next)->next;	
				return (1);
			}
		}
	return (0);
}
