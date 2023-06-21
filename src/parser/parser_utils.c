/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:13:00 by alaaouam          #+#    #+#             */
/*   Updated: 2023/05/20 12:59:25 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_count_cmds(t_token **tokens)
{
	t_token	*token;
	size_t	count;

	token = *tokens;
	count = 0;
	while (token != NULL)
	{
		if (token->type == TYPE_CMD)
			count++;
		token = token->next;
	}
	return (count);
}

size_t	ft_count_redirections(t_token **tokens)
{
	t_token	*token;
	size_t	count;

	token = *tokens;
	count = 0;
	while (token != NULL)
	{
		if (token->type == TYPE_APPEND
			|| token->type == TYPE_INPUT
			|| token->type == TYPE_OUTPUT)
			count++;
		token = token->next;
	}
	return (count);
}

size_t	ft_count_heredoc(t_token **tokens)
{
	t_token	*token;
	size_t	count;

	token = *tokens;
	count = 0;
	while (token != NULL)
	{
		if (token->type == TYPE_HEREDOC)
			count++;
		token = token->next;
	}
	return (count);
}
