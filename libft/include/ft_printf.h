/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:22:40 by alaaouam          #+#    #+#             */
/*   Updated: 2023/02/18 15:01:19 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../include/libft.h"
# include <stdarg.h>
# include <stdint.h>

int			ft_printf(char const *format, ...);
int			ft_putchar(char c);
int			ft_putstr(char *str);
int			ft_putnbr(int number);
int			ft_put_unsigned_int(unsigned int number);
int			ft_put_hexadecimal_lower(unsigned int number);
int			ft_put_hexadecimal_upper(unsigned int number);
int			ft_putptr(void *pointer);
int			ft_putptr_address(uintptr_t number);
int			ft_count_digits(unsigned int number);

#endif