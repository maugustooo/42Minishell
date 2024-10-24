/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-jes <gude-jes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:34:10 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/17 10:44:54 by gude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strip_quotes2(char *str)
{
	char	*new_str;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (str[0] == '\'' || str[0] == '\"')
	{
		if (len > 1 && str[len - 1] == str[0])
			new_str = ft_substr_free(str, 1, len - 2);
		else
			new_str = ft_substr_free(str, 1, len - 1);
	}
	else if (str[len - 1] == '\'' || str[len - 1] == '\"')
		new_str = ft_substr_free(str, 0, len - 1);
	else
	{
		new_str = ft_strdup(str);
		free(str);
	}
	return (new_str);
}

char	*strip_quotes(char *str)
{
	char	*new_str;
	int		len;

	if (!str || (str[0] != '\'' && str[0] != '\"'))
		return (str);
	len = ft_strlen(str);
	if (str[len - 1] == str[0])
	{
		if (len <= 2)
			new_str = ft_strdup("");
		else
			new_str = ft_substr(str, 1, len - 2);
	}
	else
		new_str = ft_strdup(str);
	free(str);
	return (new_str);
}

int	export_arg_err(t_token *token, t_mini *mini, char **key)
{
	if (key[0] != NULL)
	{
		if (ft_strchr(key[0], '+') && key[0][ft_strlen(key[0]) - 1] == '+')
		{
			key[0] = ft_substr_free(key[0], 0, ft_strlen(key[0]) - 1);
			mini->app_mode = true;
		}
		if (key[0][0] != key[0][ft_strlen(key[0]) - 1])
			key[0] = strip_quotes2(key[0]);
		else
			key[0] = strip_quotes(key[0]);
	}
	if (key[0] == NULL || !ft_isalpha_or_underscore(key[0][0])
		|| !ft_str_isalnum_or_underscore(key[0]) || ft_strcmp(key[0], "") == 0)
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_EXPORT), token->text);
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
		free_keys(&key);
	}
	free(tmp);
}
