/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:25:31 by gude-jes          #+#    #+#             */
/*   Updated: 2024/10/18 09:45:11 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr_free(const char *s, unsigned int start, size_t len)
{
	char	*res;
	char	*src;
	size_t	reslen;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
		return (ft_strdup(""));
	src = (char *)s + start;
	if (ft_strlen(src) < len)
		reslen = ft_strlen(src) + 1;
	else
		reslen = len + 1;
	res = malloc(reslen * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, src, reslen);
	free(src);
	return (res);
}

int	validate_and_split_export(t_token *token, t_mini *mini, char ***key2)
{
	char	*key;

	if (token->text[0] == '=')
	{
		ft_printf_fd(STDERR_FILENO, error_msg(ERROR_EXPORT), token->text);
		mini->return_code = 1;
		return (0);
	}
	if (!ft_find_c('=', token->text))
	{
		key = get_env_key(mini, token->text);
		if (key)
			return (free(key), 0);
		free(key);
	}
	*key2 = ft_split(token->text, '=');
	if (export_arg_err(token, mini, *key2))
		return (0);
	return (1);
}
