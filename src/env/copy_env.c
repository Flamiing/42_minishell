/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 17:12:34 by alaaouam          #+#    #+#             */
/*   Updated: 2023/05/25 14:50:43 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_copy_env(char **env)
{
	size_t	size;
	size_t	count;
	char	**shell_env;

	size = ft_arrlen(env);
	shell_env = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!shell_env)
		return (ft_print_error(ERROR_MALLOC));
	count = 0;
	while (count < size)
	{
		shell_env[count] = ft_strdup(env[count]);
		if (!shell_env[count])
		{
			ft_free_array(shell_env);
			return (NULL);
		}
		count++;
	}
	return (shell_env);
}
