/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:36:53 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/21 17:34:07 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_cmd_or_arg(t_token *prev_token)
{
	if (prev_token && prev_token->prev
		&& (prev_token->prev->type == TYPE_HEREDOC
			|| prev_token->prev->type == TYPE_INPUT))
		return (TYPE_CMD);
	if (prev_token && (prev_token->type == TYPE_CMD
			|| (prev_token->type == TYPE_ARG && !ft_is_not_arg(prev_token))
			|| prev_token->type == TYPE_APPEND
			|| prev_token->type == TYPE_INPUT
			|| prev_token->type == TYPE_HEREDOC
			|| prev_token->type == TYPE_OUTPUT))
		return (TYPE_ARG);
	return (TYPE_CMD);
}

static int	ft_get_type(char *data, t_token *prev_token, t_shell *shell)
{
	if (data[0] == TYPE_VAR)
		return (ft_cmd_or_arg(prev_token));
	else if (data[0] == TYPE_INPUT && data[1] == TYPE_INPUT)
		return (TYPE_HEREDOC);
	else if (data[0] == TYPE_OUTPUT && data[1] == TYPE_OUTPUT)
		return (TYPE_APPEND);
	else if (data[0] == TYPE_PIPE)
	{
		shell->pipe_count++;
		return (TYPE_PIPE);
	}
	else if (data[0] == TYPE_INPUT)
		return (TYPE_INPUT);
	else if (data[0] == TYPE_OUTPUT)
		return (TYPE_OUTPUT);
	else
		return (ft_cmd_or_arg(prev_token));
}

t_token	*ft_last_token(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next != NULL)
		tokens = tokens->next;
	return (tokens);
}

static void	ft_add_token_end(t_token **tokens, t_token *new)
{
	t_token	*last;

	if (*tokens == NULL)
		*tokens = new;
	else
	{
		last = ft_last_token(*tokens);
		last->next = new;
		new->prev = last;
	}
}

t_token	*ft_create_token(t_token **tokens, char *data, t_shell *shell)
{
	t_token	*token;

	token = (t_token *)malloc(1 * sizeof(t_token));
	if (!token)
		return (NULL);
	token->data = data;
	token->prev = ft_last_token(*tokens);
	token->next = NULL;
	token->type = ft_get_type(data, token->prev, shell);
	ft_add_token_end(tokens, token);
	return (*tokens);
}
