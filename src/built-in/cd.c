/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:58:57 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 11:10:15 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_wrong_cd_argument(char *argument)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putchar_fd(argument[0], 2);
	ft_putchar_fd(argument[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("cd: usage: cd [dir]\n", 2);
	g_status.cd_status = 1;
}

static void	ft_cd_error(char *argument)
{
	ft_putstr_fd("minishell: cd: ", 2);
	perror(argument);
	g_status.cd_status = 1;
}

int	ft_is_empty(char *arg)
{
	size_t	count;

	count = 0;
	while (arg[count])
	{
		if (arg[count] != '\0' || arg[count] != ' '
			|| (arg[count] <= 8 || arg[count] > 13))
			return (0);
		count++;
	}
	return (1);
}

static void	ft_add_oldpwd(t_shell *shell)
{
	char	**args;
	size_t	count;

	args = (char **)ft_calloc(3, sizeof(char *));
	if (!args)
		return ;
	count = 0;
	while (shell->env[count])
	{
		if (ft_strncmp(shell->env[count], "PWD=", 4) == 0)
		{
			args[0] = ft_strjoin("OLDPWD=", shell->env[count] + 4);
			break ;
		}
		count++;
	}
	args[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	ft_export(shell, args);
	free(args[1]);
	free(args);
}

void	ft_cd(t_shell *shell, char **args)
{
	size_t	args_count;

	args_count = ft_arrlen(args);
	g_status.cd_status = 0;
	if (args_count > 1 && args[1][0] == '-' && args[1][1])
		ft_wrong_cd_argument(args[1]);
	else if (args_count == 1)
	{
		if (chdir(shell->home_dir) != 0)
			ft_cd_error(shell->home_dir);
		ft_add_oldpwd(shell);
	}
	else
	{
		if (args[1][0] == '.' && args[1][1] == '\0')
			return ;
		if (chdir(args[1]) != 0)
		{
			if (ft_is_empty(args[1]))
				return ;
			g_status.cd_status = 1;
			ft_cd_error(args[1]);
		}
		ft_add_oldpwd(shell);
	}
}
