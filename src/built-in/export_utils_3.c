/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:06:05 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 11:07:28 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_is_valid_export(char **args, size_t id)
{
	size_t	count;

	count = 0;
	if (!ft_last_repeated(args, id))
		return (-1);
	if ((args[id][0] != ' ' && (args[id][0] < 8 || args[id][0] > 13)))
	{
		while (args[id][count])
		{
			if (!ft_isalpha(args[id][count]) && args[id][count] != '+'
				&& args[id][count] != '=' && args[id][count] != '_')
				return (0);
			if (count > 0 && args[id][count] == '=')
				return (1);
			count++;
		}
	}
	else if (args[id][0] == ' ' || (args[id][0] > 8 && args[id][0] <= 13))
		return (0);
	return (-2);
}

void	ft_export_without_args(t_shell *shell)
{
	size_t	count;
	size_t	pos;

	count = 0;
	while (shell->env[count])
	{
		pos = 0;
		printf("declare -x ");
		while (shell->env[count][pos] != '=')
		{
			printf("%c", shell->env[count][pos]);
			pos++;
		}
		printf("%c", shell->env[count][pos]);
		printf("\"");
		printf("%s", shell->env[count] + (pos + 1));
		printf("\"\n");
		count++;
	}
	g_status.exit_status = 0;
}
