/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:34:41 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 11:10:31 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_find_var(char **env, char *arg, size_t len)
{
	size_t	count;

	count = 0;
	while (env[count])
	{
		if (ft_strncmp(env[count], arg, len) == 0
			&& len == ft_strlen_x(env[count], '='))
			return (env[count]);
		count++;
	}
	return (NULL);
}

int	ft_last_repeated(char **args, size_t id)
{
	size_t	count;
	size_t	arg_len;
	size_t	len;
	size_t	last_found;
	size_t	reference;

	count = 0;
	arg_len = ft_strlen_x(args[id], '=');
	last_found = 0;
	while (args[count])
	{
		len = ft_strlen_x(args[count], '=');
		if (ft_strncmp(args[count], args[id], arg_len) == 0
			&& arg_len == len)
		{
			last_found++;
			if (count == id)
				reference = last_found;
		}
		count++;
	}
	if (reference == last_found)
		return (1);
	else
		return (0);
}

int	ft_has_plus_simbol(char *str)
{
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count])
	{
		if (str[count] == '+')
			return (1);
		count++;
	}
	return (0);
}

static size_t	ft_size_without_char(char *str, char c)
{
	size_t	count;
	size_t	size;

	count = 0;
	size = 0;
	while (str[count])
	{
		if (str[count] != c)
			size++;
		count++;
	}
	return (size);
}

char	*ft_remove_char(char *str, char remove)
{
	size_t	count;
	size_t	pos;
	size_t	size;
	char	*new_str;

	count = 0;
	pos = 0;
	size = ft_size_without_char(str, remove);
	new_str = (char *)ft_calloc(size + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[count])
	{
		if (str[count] != remove)
		{
			new_str[pos] = str[count];
			pos++;
		}
		count++;
	}
	return (new_str);
}
