/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:04:20 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/21 18:13:10 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_is_special_char(char *str)
{
	if (ft_strncmp(str, "$\\n", 3) == 0)
		return ('\n');
	else if (ft_strncmp(str, "$\\r", 3) == 0)
		return ('\r');
	else if (ft_strncmp(str, "$\\t", 3) == 0)
		return ('\t');
	else
		return (0);
}

void	ft_printstr(char *str)
{
	size_t	count;
	int		is_special;

	if (!str)
		return ;
	count = 0;
	while (str[count])
	{
		is_special = ft_is_special_char(str + count);
		if (is_special != 0)
		{
			printf("%c", is_special);
			count += 3;
		}
		else
		{
			printf("%c", str[count]);
			count++;
		}	
	}
}
