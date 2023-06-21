/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:40:03 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 12:16:30 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_more_redir_error(t_shell *shell, t_token *token, int type)
{
	if (token->next && token->next->type == TYPE_INPUT && type == TYPE_OUTPUT)
		return (ft_parser_error(shell, SYNTAX, token->next->type));
	if (token->next && token->next->type == TYPE_OUTPUT && type == TYPE_INPUT)
		return (ft_parser_error(shell, SYNTAX, token->next->type));
	return (0);
}
