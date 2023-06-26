/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:08:22 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/26 12:14:16 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_close_files(t_cmd *cmd, size_t size)
{
	size_t	count;

	count = 0;
	while (count < size)
	{
		if (cmd[count].infile >= 0)
			close(cmd[count].infile);
		if (cmd[count].outfile >= 0)
			close(cmd[count].outfile);
		count++;
	}
}
