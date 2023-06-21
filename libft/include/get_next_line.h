/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:59:47 by alaaouam          #+#    #+#             */
/*   Updated: 2023/02/18 14:43:28 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

void				*ft_reallocstr(char	*str, ssize_t	nbytes);
void				*ft_freeptr(void	*ptr);
char				*get_next_line(int fd);
char				*ft_strcpy(char *dst, char *src, char limit);
size_t				ft_strchr(const char *s, int c);
size_t				ft_linelen(const char *line, char limit);

#endif