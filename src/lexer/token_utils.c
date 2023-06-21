/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:10:44 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 12:11:16 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_is_not_arg(t_token *tokens)
{
	t_token	*token;

	if (!tokens)
		return (1);
	token = tokens;
	while (token != NULL)
	{
		if (token->type == TYPE_CMD
			|| token->type == TYPE_OUTPUT || token->type == TYPE_APPEND)
			break ;
		token = token->prev;
	}
	if ((token && (token->type == TYPE_APPEND || token->type == TYPE_OUTPUT)
			&& (!token->prev || (token->prev
					&& token->prev->type == TYPE_PIPE))))
		return (1);
	else
		return (0);
}
