/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remove_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:49:09 by alaaouam          #+#    #+#             */
/*   Updated: 2023/05/20 13:05:14 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_is_oposite(char c, int mode)
{
	int	opposite;

	if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
	{
		if (mode == SINGLE_QUOTE)
			opposite = DOUBLE_QUOTE;
		else
			opposite = SINGLE_QUOTE;
		if (c == opposite)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

static int	ft_do_not_remove(char c, int inside, int inside_opposite, int mode)
{
	if ((inside == 1 && c != mode)
		|| (c != SINGLE_QUOTE && c != DOUBLE_QUOTE)
		|| (inside_opposite == 1 && c == mode))
		return (1);
	else
		return (0);
}

static int	ft_has_to_copy(char *str, size_t limit, int mode)
{
	size_t	count;
	int		inside;
	int		inside_opposite;

	count = 0;
	inside = 0;
	inside_opposite = 0;
	while (count != limit)
	{
		if (ft_is_oposite(str[count], mode) && inside == 0)
			inside_opposite++;
		if (str[count] == mode && inside_opposite == 0)
			inside++;
		if (inside == 2)
			inside = 0;
		if (inside_opposite == 2)
			inside_opposite = 0;
		count++;
	}
	if (ft_do_not_remove(str[count], inside, inside_opposite, mode))
		return (1);
	return (0);
}

size_t	ft_size_without_quotes(char *str, int mode)
{
	size_t	count;
	size_t	size;
	int		inside;
	int		inside_opposite;

	count = 0;
	size = 0;
	inside = 0;
	inside_opposite = 0;
	while (str[count])
	{
		if (ft_is_oposite(str[count], mode) && inside == 0)
			inside_opposite++;
		if (str[count] == mode && inside_opposite == 0)
			inside++;
		if (ft_do_not_remove(str[count], inside, inside_opposite, mode))
			size++;
		if (inside == 2)
			inside = 0;
		if (inside_opposite == 2)
			inside_opposite = 0;
		count++;
	}
	return (size);
}

char	*ft_remove_quotes(char *str, size_t size, char *first_quote)
{
	char	*new_str;
	size_t	count;
	size_t	pos;

	new_str = (char *)ft_calloc(size + 1, sizeof(char));
	if (!new_str)
		return (str);
	count = 0;
	pos = 0;
	while (str[count])
	{
		if (ft_has_to_copy(str, count, first_quote[0]))
		{
			new_str[pos] = str[count];
			pos++;
		}
		count++;
	}
	free(str);
	return (new_str);
}
