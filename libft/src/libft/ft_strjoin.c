/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:52:35 by alaaouam          #+#    #+#             */
/*   Updated: 2023/03/15 10:51:30 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_str;

	if (!s1)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = (char *)malloc((sizeof(char) * (s1_len + s2_len)) + 1);
	if (!new_str)
		return (0);
	ft_memmove(new_str, (char *)s1, s1_len);
	ft_memmove(new_str + s1_len, (char *)s2, s2_len + 1);
	return (new_str);
}
