/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:38:34 by alaaouam          #+#    #+#             */
/*   Updated: 2023/03/15 10:52:08 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_strllen(const char *s, size_t maxlen)
{
	size_t	count;

	count = 0;
	while (s[count] && count < maxlen)
		count++;
	return (count);
}

static char	*ft_make_string(char *dst, const char *s, size_t index, size_t len)
{
	size_t	count;

	count = 0;
	while (s[index] && count < len)
	{
		dst[count] = s[index];
		index++;
		count++;
	}
	dst[count] = '\0';
	return (dst);
}

static char	*ft_create_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	max;
	size_t	size;

	max = ft_strlen(s);
	size = ft_strllen(s + start, len) + 1;
	sub_str = (char *)malloc(sizeof(char) * size);
	if (!sub_str)
		return (0);
	if (len > max)
		ft_make_string(sub_str, s, start, max);
	else
		ft_make_string(sub_str, s, start, len);
	return (sub_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	max;

	max = ft_strlen(s);
	if (start >= max)
	{
		sub_str = (char *)malloc(1);
		if (!sub_str)
			return (0);
		sub_str[0] = '\0';
		return (sub_str);
	}
	else
		sub_str = ft_create_substr(s, start, len);
	return (sub_str);
}
