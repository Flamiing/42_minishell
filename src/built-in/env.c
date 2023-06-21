/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:59:45 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/02 17:32:34 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(char **env)
{
	size_t	count;

	if (!env)
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		return (1);
	}
	count = 0;
	while (env[count])
	{
		printf("%s\n", env[count]);
		count++;
	}
	g_status.exit_status = 0;
	return (0);
}
