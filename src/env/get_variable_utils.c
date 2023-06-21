/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 12:49:55 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/21 18:06:06 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_varlen(char *var)
{
	size_t	len;

	len = 0;
	while (var[len] && (ft_isalnum(var[len])
			|| var[len] == '_' || var[len] == '$'))
	{
		if (len > 0 && var[len] == '$')
			break ;
		len++;
	}
	return (len);
}

size_t	ft_strllen(char *str, char limit, int mode, size_t stop)
{
	size_t	pos;

	pos = 0;
	if (limit == '\0' || mode == 1)
	{
		while (str[pos])
		{
			if (mode == 1 && str[pos] == '$' && pos == stop)
				break ;
			pos++;
		}
		return (pos);
	}
	while (str[pos] && (ft_isalnum(str[pos]) || str[pos] == '_'
			|| str[pos] == SINGLE_QUOTE || str[pos] == DOUBLE_QUOTE))
	{
		pos++;
	}
	return (pos);
}

char	*ft_joinstr(char *start, char *mid, size_t stop)
{
	char	*new_str;
	size_t	size;
	size_t	size_start;
	size_t	size_mid;
	size_t	size_end;

	size = ft_strllen(start, DOUBLE_QUOTE, 0, stop) + 1;
	size_start = ft_strllen(start, '$', 1, stop);
	size_mid = ft_strllen(mid, '\0', 0, stop);
	size_end = ft_strllen(start + (size - 1), '\0', 0, stop);
	new_str = (char *)ft_calloc((size_start + size_mid + size_end + 1),
			sizeof(char));
	if (!new_str)
		return (ft_print_error(ERROR_MALLOC));
	ft_strlcat(new_str, start, size_start + 1);
	ft_strlcat(new_str + size_start, mid, size_start + size_mid + 1);
	ft_strlcat(new_str, start + (size_start + ft_varlen(start + size_start)),
		size_start + size_mid + size_end + 1);
	free(mid);
	return (new_str);
}

size_t	ft_len_no_spaces(char *str)
{
	size_t	count;
	size_t	size;

	if (!str)
		return (0);
	count = 0;
	size = 0;
	while (str[count])
	{
		if (str[count] != ' ' && (str[count] < 8 || str[count] > 13))
		{
			size++;
			count++;
		}
		else
		{
			size++;
			while (str[count] == ' ' || (str[count] > 8 && str[count] <= 13))
				count++;
		}
	}
	return (size);
}

int	ft_is_special_space(char *str)
{
	if (ft_strncmp(str, "$'\\n'", 4) == 0)
		return ('\n');
	else if (ft_strncmp(str, "$'\\r'", 4) == 0)
		return ('\r');
	else if (ft_strncmp(str, "$'\\t'", 4) == 0)
		return ('\t');
	else
		return (0);
}
