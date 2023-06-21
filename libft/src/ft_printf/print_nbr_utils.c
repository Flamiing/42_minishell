/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:42:54 by alaaouam          #+#    #+#             */
/*   Updated: 2023/03/15 10:53:03 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_putnbr(int number)
{
	int	count;

	if (number < 0)
		count = ft_count_digits(number * -1);
	else
		count = ft_count_digits(number);
	ft_putnbr_fd(number, 1);
	if (number <= 0)
		count++;
	return (count);
}

int	ft_put_unsigned_int(unsigned int number)
{
	int	count;

	count = ft_count_digits(number);
	if (number < 10)
		ft_putchar_fd(number + 48, 1);
	else
	{
		ft_put_unsigned_int(number / 10);
		ft_put_unsigned_int(number % 10);
	}
	if (number == 0)
		count++;
	return (count);
}

int	ft_put_hexadecimal_lower(unsigned int number)
{
	int		count;
	int		index;
	char	hexadecimal[12];

	count = 0;
	index = 0;
	if (number == 0)
	{
		ft_putchar_fd('0', 1);
		count++;
	}
	while (number != 0)
	{
		hexadecimal[index] = "0123456789abcdef"[number % 16];
		number /= 16;
		index++;
		count++;
	}
	index--;
	while (index >= 0)
	{
		ft_putchar_fd(hexadecimal[index], 1);
		index--;
	}
	return (count);
}

int	ft_put_hexadecimal_upper(unsigned int number)
{
	int		count;
	int		index;
	char	hexadecimal[12];

	count = 0;
	index = 0;
	if (number == 0)
	{
		ft_putchar_fd('0', 1);
		count++;
	}
	while (number != 0)
	{
		hexadecimal[index] = "0123456789ABCDEF"[number % 16];
		number /= 16;
		index++;
		count++;
	}
	index--;
	while (index >= 0)
	{
		ft_putchar_fd(hexadecimal[index], 1);
		index--;
	}
	return (count);
}
