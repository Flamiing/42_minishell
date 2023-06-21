/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 03:12:56 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 12:16:46 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_pipe_check(t_shell *shell, t_token *token)
{
	if (token->next && token->next->type == TYPE_PIPE
		&& (token->type == TYPE_INPUT
			|| token->type == TYPE_OUTPUT
			|| token->type == TYPE_HEREDOC
			|| token->type == TYPE_APPEND))
		return (ft_parser_error(shell, SYNTAX, TYPE_PIPE));
	if (shell->cmd_count != 0 && shell->cmd_list_size == shell->pipe_count)
	{
		if (token->prev && token->type == TYPE_PIPE
			&& token->prev->type != TYPE_ARG
			&& token->prev->type != TYPE_INPUT
			&& token->prev->type != TYPE_OUTPUT
			&& token->prev->type != TYPE_HEREDOC
			&& token->prev->type != TYPE_APPEND)
			return (ft_parser_error(shell, SYNTAX, 0));
		else
			return (ft_parser_error(shell, SYNTAX, TYPE_PIPE));
	}
	return (0);
}

static int	ft_syntax_quotes_check(t_token *token, int type)
{
	if (type == TYPE_CMD || type == TYPE_ARG)
	{
		if (ft_has_quotes(token->data) && ft_not_closed(token->data))
			return (1);
	}
	return (0);
}

static int	ft_syntax_error(t_token *token, int type)
{
	if (token->prev != NULL)
	{
		if (token->next && type == TYPE_HEREDOC
			&& token->prev->type == TYPE_HEREDOC)
			return (2);
		if (type == TYPE_APPEND && token->prev->type == TYPE_APPEND)
			return (3);
		if (token->prev && token->prev->type != type
			&& type == TYPE_OUTPUT && token->next == NULL)
			return (4);
		if (token->prev && token->prev->type != type
			&& token->prev->type != TYPE_HEREDOC
			&& type == TYPE_INPUT && token->next == NULL)
			return (5);
		if (token->prev->type == type && token->prev->type != TYPE_ARG
			&& !ft_is_empty_with_quotes(token->prev->data))
			return (1);
	}
	else if ((type == TYPE_PIPE && !token->prev)
		|| (type == TYPE_APPEND && token->next == NULL))
		return (1);
	return (ft_syntax_quotes_check(token, type));
}

static int	ft_general_syntax_check(t_shell *shell, t_token *token)
{
	if (token->next == NULL && (token->type == TYPE_HEREDOC
			|| token->type == TYPE_APPEND))
		return (ft_parser_error(shell, SYNTAX, TYPE_NEWLINE));
	if (ft_syntax_error(token, token->type) == 2)
		return (ft_parser_error(shell, SYNTAX, TYPE_OTHERS));
	else if (ft_syntax_error(token, token->type) == 3)
		return (ft_parser_error(shell, SYNTAX, TYPE_APPEND));
	else if (ft_syntax_error(token, token->type) == 4)
		return (ft_parser_error(shell, SYNTAX, TYPE_NEWLINE));
	else if (ft_syntax_error(token, token->type) == 5)
		return (ft_parser_error(shell, SYNTAX, TYPE_INPUT));
	if (token->next && token->type == TYPE_OUTPUT
		&& token->next->type == TYPE_PIPE && token->next->next == NULL)
		return (ft_parser_error(shell, SYNTAX, TYPE_NEWLINE));
	if (ft_pipe_check(shell, token) != 0
		|| ft_redirection_error(shell, token, token->type))
		return (SYNTAX);
	if (token->next && token->type == TYPE_HEREDOC
		&& token->next->type == TYPE_APPEND)
		return (ft_parser_error(shell, SYNTAX, TYPE_APPEND));
	if (token->next && (token->type == TYPE_APPEND
			|| token->type == TYPE_HEREDOC)
		&& token->next->type == TYPE_OUTPUT)
		return (ft_parser_error(shell, SYNTAX, token->next->type));
	return (0);
}

int	ft_has_syntax_error(t_shell *shell, t_token **tokens)
{
	t_token	*token;

	token = *tokens;
	while (token != NULL)
	{
		if (ft_general_syntax_check(shell, token) != 0)
			return (SYNTAX);
		if (token->next == NULL && ((!token->prev
					&& (token->type == TYPE_INPUT
						|| token->type == TYPE_OUTPUT
						|| token->type == TYPE_HEREDOC
						|| token->type == TYPE_APPEND))
				|| (token->prev && token->prev->type == TYPE_HEREDOC
					&& token->type == TYPE_INPUT)))
			return (ft_parser_error(shell, SYNTAX, TYPE_NEWLINE));
		if (token->next && token->type == TYPE_APPEND
			&& token->next->type == TYPE_HEREDOC)
			return (ft_parser_error(shell, SYNTAX, TYPE_OTHERS));
		if (ft_syntax_error(token, token->type))
			return (ft_parser_error(shell, SYNTAX, token->type));
		if (shell->cmd_count + shell->redir_count < shell->pipe_count)
			return (ft_parser_error(shell, SYNTAX, TYPE_PIPE));
		token = token->next;
	}
	return (0);
}
