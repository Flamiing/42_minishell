/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:53:03 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/03 00:44:29 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_quotes_truncated(char *str)
{
	size_t	count;
	int		inside_single;
	int		inside_double;
	char	first_quote;

	count = 0;
	inside_single = 0;
	inside_double = 0;
	while (str[count])
	{
		if ((str[count] == '\'' || str[count] == '"') && !first_quote)
			first_quote = str[count];
		if (str[count] == SINGLE_QUOTE && inside_double == 0)
			inside_single++;
		if (inside_single == 2)
			inside_single = 0;
		if (str[count] == DOUBLE_QUOTE && inside_single == 0)
			inside_double++;
		if (inside_double == 2)
			inside_double = 0;
		count++;
	}
	if (inside_single == 1 || inside_double == 1)
		return (1);
	return (0);
}

static int	ft_next_last_quote(char *str)
{
	ssize_t	size;

	size = ft_strlen(str);
	while (size >= 0)
	{
		if (str[size] == SINGLE_QUOTE || str[size] == DOUBLE_QUOTE)
			return (str[size]);
		size--;
	}
	return (-1);
}

static int	ft_inside_not_closed(char *str, int type)
{
	size_t	count;
	size_t	quote_count;

	if (!str)
		return (0);
	count = 0;
	quote_count = 0;
	while (str[count])
	{
		if (str[count] == type)
			quote_count++;
		count++;
	}
	if (quote_count % 2 == 0)
		return (0);
	else
		return (1);
}

int	ft_not_closed(char *str)
{
	size_t	count;

	if (ft_strlen(str) == 1 || ft_quotes_truncated(str))
		return (1);
	count = 0;
	while (str[count])
	{
		if ((str[count] == SINGLE_QUOTE || str[count] == DOUBLE_QUOTE)
			&& str[count] == ft_next_last_quote(str + (count + 1)))
		{
			if (!ft_inside_not_closed(str, str[count]))
				return (0);
		}
		count++;
	}
	return (1);
}

int	ft_redirection_error(t_shell *shell, t_token *token, int type)
{
	if (token->prev)
	{
		if ((type == TYPE_APPEND || type == TYPE_HEREDOC)
			&& token->prev->type == TYPE_INPUT)
		{
			if (type == TYPE_HEREDOC)
				return (ft_parser_error(shell, SYNTAX, type + 1));
			return (ft_parser_error(shell, SYNTAX, type));
		}
		if ((type == TYPE_APPEND || type == TYPE_HEREDOC)
			&& token->prev->type == TYPE_OUTPUT)
		{
			if (type == TYPE_HEREDOC)
				return (ft_parser_error(shell, SYNTAX, type + 1));
			return (ft_parser_error(shell, SYNTAX, type));
		}
		if ((type == TYPE_INPUT || type == TYPE_OUTPUT)
			&& token->prev->type == TYPE_APPEND)
			return (ft_parser_error(shell, SYNTAX, type));
		if ((type == TYPE_INPUT || type == TYPE_OUTPUT)
			&& token->prev->type == TYPE_HEREDOC)
			return (ft_parser_error(shell, SYNTAX, type));
	}
	return (ft_more_redir_error(shell, token, type));
}
