/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:53:59 by alaaouam          #+#    #+#             */
/*   Updated: 2023/03/15 10:51:51 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index;
	size_t	pos;

	index = 0;
	pos = 0;
	if (needle[pos] == '\0')
		return ((char *)haystack);
	while (haystack[index] != '\0')
	{
		pos = 0;
		while (haystack[index + pos] == needle[pos]
			&& (haystack[index + pos] != '\0' && (index + pos) < len))
			pos++;
		if (needle[pos] == '\0')
			return ((char *)haystack + index);
		index++;
	}
	return (0);
}
