/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:05:02 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/23 12:50:27 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_remove_quotes_valid(char *cmd, int can_remove_quotes, int type)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (((ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0 && len == 4)
			|| (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0 && len == 2)
			|| (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0 && len == 3)
			|| (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0 && len == 6)
			|| (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0 && len == 5)
			|| (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0 && len == 3)
			|| (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0 && len == 4)
			|| type != CMD_BUILT_IN) && can_remove_quotes)
		return (1);
	return (0);
}

static size_t	ft_count_quotes(char *buffer, int type)
{
	size_t	counter;
	size_t	count;

	counter = 0;
	count = 0;
	while (buffer[count])
	{
		if (buffer[count] == type)
			counter++;
		count++;
	}
	return (counter);
}

size_t	ft_out_of_quotes(char *buffer, int type)
{
	size_t	quote_counter;
	size_t	pos;
	size_t	count;
	int		opposite;

	quote_counter = ft_count_quotes(buffer, type);
	pos = 0;
	count = 0;
	opposite = 0;
	while (buffer[pos])
	{
		if (buffer[pos] == type)
			count++;
		if (buffer[pos] == ft_get_opposite(type))
			opposite++;
		if (count == quote_counter && (opposite == 0
				&& (buffer[pos] == ' '
					|| (buffer[pos] > 8 && buffer[pos] <= 13))))
			return (pos);
		if (opposite == 2)
			opposite = 0;
		pos++;
	}
	return (pos);
}

static int	ft_is_inside_quotes(char *str, size_t pos)
{
	size_t	count;
	int		inside_single;
	int		inside_double;

	count = 0;
	inside_single = 0;
	inside_double = 0;
	while (count < pos)
	{
		if (str[count] == SINGLE_QUOTE)
			inside_single++;
		if (inside_single == 2)
			inside_single = 0;
		if (str[count] == DOUBLE_QUOTE)
			inside_double++;
		if (inside_double == 2)
			inside_double = 0;
		count++;
	}
	if (inside_single == 1 || inside_double == 1)
		return (1);
	else
		return (0);
}

int	ft_not_inside_quotes(char *str)
{
	size_t	count;

	if (!str)
		return (1);
	count = 0;
	while (str[count])
	{
		if (str[count] == '$' && ft_is_inside_quotes(str, count))
			return (0);
		count++;
	}
	return (1);
}
