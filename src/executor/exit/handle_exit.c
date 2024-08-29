/**
 * @defgroup mandatory Mandatory
 * @{
 * @file handle_exit.c
 * @brief Handles the exit
*/

#include "minishell.h"

/**
 * @brief Handles the exit command
 * 
 * @param prev_dir Free previous_dir
*/
void    handle_exit(t_token **token, t_mini *mini)
{
    //TODO: FREE LIST
	free_things(mini);
	freethem(token, mini);
    exit(mini->return_code);
}

/**@}*/