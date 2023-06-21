/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:49:29 by alaaouam          #+#    #+#             */
/*   Updated: 2023/05/07 18:26:31 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_chrcnt_left(const char *s1, const char *set)
{
	size_t	index;
	size_t	remove;

	index = 0;
	remove = 0;
	while (s1[index])
	{
		if (ft_strchr(set, s1[index]) != 0)
			remove++;
		else
			break ;
		index++;
	}
	return (remove);
}

static size_t	ft_chrcnt_right(const char *s1, const char *set)
{
	size_t	index;
	size_t	remove;

	index = ft_strlen(s1) - 1;
	remove = 0;
	while (s1[index])
	{
		if (ft_strchr(set, s1[index]) != 0)
			remove++;
		else
			break ;
		index--;
	}
	return (remove);
}

static char	*ft_trim(char *dst, const char *src, size_t	start, size_t end)
{
	size_t	index;

	index = 0;
	while (start < end)
	{
		dst[index] = src[start];
		index++;
		start++;
	}
	dst[index] = '\0';
	return (dst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	remove;
	size_t	end;
	char	*new_str;

	if (!s1 || !set)
		return (0);
	remove = ft_chrcnt_left(s1, set) + ft_chrcnt_right(s1, set);
	end = ft_strlen(s1);
	if (remove > end)
	{
		new_str = (char *)malloc(1);
		new_str[0] = '\0';
		return (new_str);
	}
	new_str = (char *)malloc((sizeof(char) * (end - remove) + 1));
	if (!new_str)
		return (0);
	start = ft_chrcnt_left(s1, set);
	end -= ft_chrcnt_right(s1, set);
	new_str = ft_trim(new_str, s1, start, end);
	return (new_str);
}
