/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:05:26 by maugusto          #+#    #+#             */
/*   Updated: 2024/07/31 18:21:41 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief free the params
 * 
 * @param token the list of tokens
 * @param splited the tokens splited
 */
void freethem(t_token **token, char **splited)
{
	if(token)
		ft_tokenclear(token);	
	if(splited)
		free(splited);
}