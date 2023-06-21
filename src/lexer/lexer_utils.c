/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:01:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/01 12:08:08 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_type(char c)
{
	if (ft_isalnum(c))
		return (WORD);
	else if (c == VARIABLE)
		return (VARIABLE);
	else if (c == PIPE)
		return (PIPE);
	else if (c == ARGUMENT || c == UNDERSCORE)
		return (ARGUMENT);
	else if (c == IN_BRACKET || c == OUT_BRACKET)
		return (ANGLE_BRACKETS);
	else if (c == SINGLE_QUOTE)
		return (SINGLE_QUOTE);
	else if (c == DOUBLE_QUOTE)
		return (DOUBLE_QUOTE);
	else
		return (OTHERS);
}

int	ft_space_alone(char *buffer, size_t pos)
{
	size_t	count;
	int		quote_found;
	int		reference;

	count = 0;
	quote_found = 0;
	reference = 0;
	while (count < pos)
	{
		if ((buffer[count] == SINGLE_QUOTE || buffer[count] == DOUBLE_QUOTE)
			&& (reference == 0 || buffer[count] == reference))
		{
			reference = buffer[count];
			quote_found++;
		}
		if (quote_found == 2)
			quote_found = 0;
		count++;
	}
	if ((buffer[count] == ' ' || (buffer[count] > 8 && buffer[count] <= 13))
		&& quote_found != 1)
		return (1);
	return (0);
}
