/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:03:38 by alaaouam          #+#    #+#             */
/*   Updated: 2023/04/01 17:56:21 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_strcnt(char const *s, char c)
{
	size_t	index;
	size_t	count;
	size_t	len;

	index = 0;
	count = 0;
	len = ft_strlen(s);
	while (index < len)
	{
		if ((s[index + 1] == '\0' || s[index + 1] == c)
			&& (s[index] != '\0' && s[index] != c))
			count++;
		index++;
	}
	return (count);
}

static size_t	ft_free_array(char **arr)
{
	size_t	index;

	index = 0;
	if (!arr)
		return (0);
	while (arr[index])
	{
		free(arr[index]);
		index++;
	}
	free(arr);
	return (0);
}

static char	*ft_strtok(char const *s, char c)
{
	size_t	count;
	size_t	index;
	size_t	len;
	char	*token;

	index = 0;
	len = 0;
	while (s[index] == c)
		index++;
	count = index;
	while (s[count] && s[count] != c)
	{
		count++;
		len++;
	}
	token = (char *)malloc(len + 1);
	if (!token)
		return (0);
	ft_strlcpy(token, (char *)&s[index], len + 1);
	return (token);
}

static	void	*ft_addtok(char **dst, char const *src, char c, size_t items)
{
	size_t	index;
	size_t	item;
	char	*token;

	index = 0;
	item = 0;
	while (src[index])
	{
		if ((src[index] == c && src[index + 1] != '\0'
				&& src[index + 1] != c && item < items)
			|| (index == 0 && src[index] != '\0' && src[index] != c))
		{
			token = ft_strtok(&src[index], c);
			if (!token)
				return (0);
			dst[item] = token;
			if (!dst[item])
				return (0);
			item++;
		}
		index++;
	}
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	size_t	items;
	char	**strarr;

	if (!s)
		return (0);
	items = ft_strcnt(s, c);
	strarr = (char **)ft_calloc(items + 1, sizeof(char *));
	if (!strarr)
		return (0);
	if (ft_addtok(strarr, s, c, items) == 0)
	{
		ft_free_array(strarr);
		return (0);
	}
	strarr[items] = 0;
	return (strarr);
}
