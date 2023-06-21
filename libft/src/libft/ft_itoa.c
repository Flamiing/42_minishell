/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:49:58 by alaaouam          #+#    #+#             */
/*   Updated: 2023/03/15 10:50:08 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static	size_t	ft_count_digits(long long n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_negative(char *str, long long n, size_t size)
{
	size_t	count;

	count = size;
	str = (char *)malloc((sizeof(char) * size) + 2);
	if (!str)
		return (0);
	n *= -1;
	count++;
	while (count--)
	{
		str[count] = n % 10 + 48;
		n /= 10;
	}
	str[0] = '-';
	str[size + 1] = '\0';
	return (str);
}

static char	*ft_positive(char *str, long long n, size_t size)
{
	size_t	count;

	count = size;
	str = (char *)malloc((sizeof(char) * size) + 1);
	if (!str)
		return (0);
	while (count--)
	{
		str[count] = n % 10 + 48;
		n /= 10;
	}
	str[size] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	size_t		size;

	str = 0;
	size = ft_count_digits(n);
	if (n < 0)
	{
		str = ft_negative(str, n, size);
		if (!str)
			return (0);
	}
	else
	{
		str = ft_positive(str, n, size);
		if (!str)
			return (0);
	}
	return (str);
}
