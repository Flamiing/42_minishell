/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:23:21 by alaaouam          #+#    #+#             */
/*   Updated: 2023/05/08 23:40:11 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	count;
	size_t	limit;

	if (dstsize == 0 && !dst)
		return (0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	count = 0;
	limit = dstsize - dst_len - 1;
	if (dstsize == 0)
		return (src_len);
	if (dstsize < dst_len)
		return (src_len + dstsize);
	if (dst_len < dstsize)
	{
		while (src[count] && count < limit)
		{
			dst[count + dst_len] = src[count];
			count++;
		}
		dst[count + dst_len] = '\0';
	}
	return (src_len + dst_len);
}
