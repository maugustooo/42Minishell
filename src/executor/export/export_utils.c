/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:34:10 by gude-jes          #+#    #+#             */
/*   Updated: 2024/09/25 09:55:49 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_arg_err(t_token *token, t_mini *mini, char **key)
{
	if ((key[0] == NULL)
		|| (!ft_str_isalpha(key[0]) && !ft_strchr(key[0], '_')))
	{
		ft_printf_fd(STDERR_FILENO, Error_Msg(ERROR_EXPORT), token->text);
		mini->return_code = 1;
		mini->exported = true;
		free_keys(&key);
		return (1);
	}
	return (0);
}
void	check_export_expander(t_token *token, t_mini *mini)
{
	char	*tmp;
	char	**key;
	char	*expanded_value;

	tmp = ft_strdup(token->text);
	expander(&token, mini);
	if (ft_strcmp(token->text, "") == 0)
	{
		key = ft_split(tmp, '=');
		if (key[0])
		{
			expanded_value = ft_strjoin(key[0], "=");
			change_token_text(token, expanded_value);
		}
		free_key(key);
	}
	free(tmp);
}
