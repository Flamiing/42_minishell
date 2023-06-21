/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:39:15 by alaaouam          #+#    #+#             */
/*   Updated: 2023/05/17 12:54:10 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_begin_with_space(char *str)
{
	if (!str)
		return (0);
	if (str[0] == 32)
		return (1);
	return (0);
}

char	*ft_get_with_space(char	*dest, char *cmd)
{
	if (!cmd)
		return (NULL);
	dest = (char *)malloc(ft_strlen(cmd) + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, cmd, ft_strlen(cmd) + 1);
	return (dest);
}
