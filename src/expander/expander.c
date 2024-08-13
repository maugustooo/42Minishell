/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:05:58 by maugusto          #+#    #+#             */
/*   Updated: 2024/08/13 12:06:00 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expander(char *input)
{
	char	*test;
	int		i;
	char	*var_name;
	char	*start;
	
	var_name =  NULL;
	i = -1;
	test = input;
	while (*test)
	{
		if(*test == '$')
			test++;
		start = test;
		while (*test && (ft_isalnum(*test) || *test == '_'))
			test++;
		var_name = ft_strndup(start, test - start);
		// ft_strncpy(var_name, start, test - start);
		ft_printf("%s\n", var_name);
		getenv(var_name);
	}
	return(NULL);
}