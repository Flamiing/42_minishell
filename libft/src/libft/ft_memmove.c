/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:15:34 by alaaouam          #+#    #+#             */
/*   Updated: 2023/03/15 10:50:56 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;
	unsigned char	buffer;

	if (!dst && !src)
		return (0);
	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	buffer = 0;
	if (ptr_dst < ptr_src)
		ft_memcpy(dst, src, len);
	else
	{
		while (len--)
		{
			buffer = ptr_src[len];
			ptr_dst[len] = buffer;
		}
	}
	return (dst);
}
