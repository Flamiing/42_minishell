/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:38:20 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/23 12:09:42 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	ft_count_with_quotes(char *buffer, int type, int prev_type)
{
	size_t	size;
	size_t	quote_count;
	size_t	real_size;
	int		opposite;

	quote_count = 0;
	size = 0;
	opposite = 0;
	while (buffer[size])
	{
		if (buffer[size] == type)
			quote_count++;
		if (buffer[size] == ft_get_opposite(type))
			opposite++;
		size++;
		if (quote_count == 2 && opposite == 0 && prev_type != WORD
			&& (buffer[size] == ' ' || buffer[size] == '<'
				|| buffer[size] == '>' || buffer[size] == '|'))
			break ;
		ft_reset_quote_counts(&quote_count, &opposite);
	}
	real_size = ft_out_of_quotes(buffer, type);
	if (real_size < size)
		return (real_size);
	return (size);
}

static size_t	ft_get_size(char *buffer, int type, int prev_type)
{
	size_t	size;

	size = 0;
	if (type == WORD || type == VARIABLE || type == ARGUMENT)
	{
		if (type == VARIABLE || type == ARGUMENT)
			size++;
		while (buffer[size] && buffer[size] != '<' && buffer[size] != '>'
			&& buffer[size] != '|' && !ft_space_alone(buffer, size))
			size++;
	}
	else if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
		size = ft_count_with_quotes(buffer, type, prev_type);
	else
		size++;
	return (size);
}

static size_t	ft_tokensize(char *buffer, int type, int prev_type)
{
	size_t	size;

	size = 0;
	if ((type == ANGLE_BRACKETS && ((buffer[0] == '>' && buffer[1] == '>')
				|| (buffer[0] == '<' && buffer[1] == '<'))))
		size = 2;
	else if (type == ANGLE_BRACKETS || type == PIPE)
		size++;
	else if (((buffer[0] == '.' && buffer[1] == '/')
			|| (buffer[0] == '-' && buffer[1] == '-'))
		&& ft_type(buffer[2]) == WORD)
		size = ft_get_size(buffer + 2, WORD, prev_type) + 2;
	else if ((buffer[0] == '.' && ft_type(buffer[1]) == WORD)
		|| (buffer[0] != ' ' && buffer[1] != '$'
			&& type != SINGLE_QUOTE
			&& type != DOUBLE_QUOTE))
		size = ft_get_size(buffer + 1, WORD, prev_type) + 1;
	else
		size = ft_get_size(buffer, type, prev_type);
	return (size);
}

static char	*ft_get_token_data(char *buffer, int prev_type)
{
	char	*data;
	size_t	count;
	size_t	size;

	count = 0;
	size = ft_tokensize(buffer, ft_type(buffer[count]), prev_type);
	data = (char *)ft_calloc(size + 1, sizeof(char));
	if (!data)
		return (ft_print_error(ERROR_MALLOC));
	while (buffer[count] && count < size)
	{
		data[count] = buffer[count];
		count++;
	}
	data[count] = '\0';
	return (data);
}

t_token	*ft_lexer(char *buffer, t_shell *shell)
{
	int		last_type;
	char	*data;
	size_t	count;

	count = 0;
	shell->pipe_count = 0;
	last_type = -1;
	while (buffer[count])
	{
		if (buffer[count] == ' ')
			count++;
		else
		{
			data = ft_get_token_data(buffer + count, last_type);
			if (!data)
				return (ft_free_tokens(&shell->tokens));
			if (ft_create_token(&shell->tokens, data, shell) == NULL)
				return (ft_free_tokens(&shell->tokens));
			count += ft_strlen(data);
			last_type = ft_last_token(shell->tokens)->type;
		}
	}
	return (shell->tokens);
}
