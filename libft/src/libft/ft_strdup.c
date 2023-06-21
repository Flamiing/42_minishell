/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:10:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/03/15 10:51:21 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	size_t	count;

	cpy = malloc(ft_strlen(s1) + 1);
	if (!cpy)
		return (0);
	count = 0;
	while (s1[count] != '\0')
	{
		cpy[count] = s1[count];
		count++;
	}
	cpy[count] = '\0';
	return (cpy);
}
