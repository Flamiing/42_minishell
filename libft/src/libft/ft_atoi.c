/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 21:02:56 by alaaouam          #+#    #+#             */
/*   Updated: 2023/03/15 10:49:46 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_atoi(const char *string)
{
	size_t	count;
	int		sign;
	int		number;

	count = 0;
	sign = 1;
	number = 0;
	while (string[count] == 32 || (string[count] > 8 && string[count] <= 13))
		count++;
	if (string[count] == 45 || string[count] == 43)
	{
		if (string[count] == 45)
			sign *= -1;
		count++;
	}
	while ((string[count] != '\0' && (string[count] >= 48
				&& string[count] <= 57)))
	{
		number += string[count] - 48;
		if (string[count + 1] >= 48 && string[count + 1] <= 57)
			number *= 10;
		count++;
	}
	return (number * sign);
}
