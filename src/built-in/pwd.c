/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:59:12 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/07 17:11:52 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_wrong_pwd_argument(char *argument)
{
	ft_putstr_fd("minishell: pwd: ", 2);
	ft_putchar_fd(argument[0], 2);
	ft_putchar_fd(argument[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("pwd: usage: pwd\n", 2);
	g_status.exit_status = 1;
}

void	ft_pwd(char **args)
{
	size_t	args_count;
	char	*cwd;

	args_count = ft_arrlen(args);
	if (args_count > 1 && args[1][0] == '-' && args[1][1])
		ft_wrong_pwd_argument(args[1]);
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			ft_print_error(ERROR_PWD);
			return ;
		}
		printf("%s\n", cwd);
		free(cwd);
	}
	g_status.exit_status = 0;
}
