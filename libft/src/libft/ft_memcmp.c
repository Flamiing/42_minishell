/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:05:57 by alaaouam          #+#    #+#             */
/*   Updated: 2023/03/15 10:50:49 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			count;
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	count = 0;
	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	while (count < n)
	{
		if (ptr_s1[count] != ptr_s2[count])
			return (ptr_s1[count] - ptr_s2[count]);
		count++;
	}
	return (0);
}
