/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 20:41:46 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/21 18:03:02 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_remove_spaces(char *new_str, char *str, size_t count,
	size_t size)
{
	size_t	pos;

	pos = 0;
	while (pos != size)
	{
		if (str[count] != ' ' && (str[count] < 8 || str[count] > 13))
		{
			new_str[pos] = str[count];
			pos++;
			count++;
		}
		else if (str[count] == ' ' || (str[count] > 8 && str[count] <= 13))
		{
			if (count > 0 && pos <= size)
			{
				new_str[pos] = ' ';
				pos++;
				count++;
			}
			while (str[count] == ' ' || (str[count] > 8 && str[count] <= 13))
				count++;
		}
	}
	return (new_str);
}

static char	*ft_join_and_remove_spaces(char *str, char *var, size_t full_size)
{
	size_t	size;
	char	*temp;
	char	*new_str;

	temp = ft_joinstr(var, str, full_size);
	size = ft_len_no_spaces(temp);
	new_str = (char *)ft_calloc(size + 1, sizeof(char));
	if (!new_str)
		return (temp);
	if (ft_strlen(temp) == 0)
	{
		free(new_str);
		return (temp);
	}
	new_str = ft_remove_spaces(new_str, temp, 0, size);
	free(temp);
	return (new_str);
}

char	*ft_get_var(char **env, char *var, size_t count)
{
	size_t	pos;
	char	*value;

	pos = 0;
	value = NULL;
	while (pos != count)
		pos++;
	if (ft_strncmp(var + pos, "$?", 2) == 0)
	{
		value = ft_get_value(env, var + pos, 1);
		var = ft_remove_interrogation(var, value);
		return (var);
	}
	else
		value = ft_get_value(env, var + pos, 0);
	if (!value)
	{
		free(var);
		return (NULL);
	}
	value = ft_join_and_remove_spaces(value, var, count);
	free(var);
	return (value);
}

static int	ft_not_in_quotes(char *str, size_t pos)
{
	size_t	count;
	int		inside_single;
	int		inside_double;

	count = 0;
	inside_single = 0;
	inside_double = 0;
	while (count < pos)
	{
		if (str[count] == SINGLE_QUOTE && inside_double == 0)
			inside_single++;
		if (inside_single == 2)
			inside_single = 0;
		if (str[count] == DOUBLE_QUOTE)
			inside_double++;
		if (inside_double == 2)
			inside_double = 0;
		count++;
	}
	if (inside_single == 1)
		return (0);
	else
		return (1);
}

char	*ft_get_var_values(char **env, char *var)
{
	size_t	pos;
	char	*value;

	pos = 0;
	value = var;
	while (value[pos])
	{
		if (value[pos] == '$' && ft_not_in_quotes(value, pos)
			&& ft_is_special_space(value + pos) == 0)
		{
			value = ft_get_var(env, value, pos);
			if (!value)
				return (NULL);
			pos = 0;
		}
		else
			pos++;
	}
	return (value);
}
