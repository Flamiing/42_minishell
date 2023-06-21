/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:27:00 by alaaouam          #+#    #+#             */
/*   Updated: 2023/03/15 10:52:30 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

size_t	ft_linelen(const char *line, char limit)
{
	size_t	index;

	if (!line)
		return (0);
	index = 0;
	if (limit == '\0')
	{
		while (line[index])
			index++;
	}
	else
	{
		while (line[index] && line[index] != limit)
			index++;
	}
	if (index == 0 && line[index] == '\n')
		index++;
	return (index);
}

char	*ft_strcpy(char *dst, char *src, char limit)
{
	int		index;

	if (!dst || !src)
		return (NULL);
	index = 0;
	if (limit == '\0')
	{
		while (src[index])
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	else
	{
		while (src[index] && src[index] != limit)
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = limit;
		dst[index + 1] = '\0';
	}
	return (dst);
}

size_t	ft_strchr(const char *s, int c)
{
	size_t	count;
	char	ch;

	if (!s)
		return (0);
	count = 0;
	ch = c;
	while (s[count])
	{
		if (s[count] == ch)
			return (1);
		count++;
	}
	if (s[count] == ch)
		return (1);
	return (0);
}

void	*ft_reallocstr(char	*str, ssize_t	nbytes)
{
	ssize_t	size;
	char	*temp;

	if (!str)
	{
		str = (char *)malloc(nbytes + 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	size = ft_linelen(str, '\0') + nbytes;
	temp = (char *)malloc(size + 1);
	if (!temp)
		return (NULL);
	ft_strcpy(temp, str, '\0');
	if (str)
		free(str);
	return (temp);
}

void	*ft_freeptr(void	*ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}
