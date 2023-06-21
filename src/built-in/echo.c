/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:59:00 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/21 18:14:21 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_no_newline(char *str)
{
	size_t	count;
	size_t	counter;

	if (!str)
		return (0);
	count = 0;
	counter = 0;
	if (str[count] != '-')
		return (0);
	while (str[count])
	{
		if (str[count] == '-')
			counter++;
		if (str[count] != 'n' && str[count] != '-')
			return (0);
		count++;
	}
	if (counter > 1)
		return (0);
	return (1);
}

void	ft_no_path_error(char *raw_cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(raw_cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("no such a file or directory\n", 2);
	g_status.exit_status = 1;
}

static int	ft_no_path(char *cmd_path, char *raw_cmd)
{
	if (ft_strncmp(cmd_path, "echo", 4) == 0 && ft_strlen(cmd_path) == 4)
	{
		ft_no_path_error(raw_cmd);
		return (1);
	}
	return (0);
}

static void	ft_print_arguments(char **args)
{
	size_t	count;

	count = 1;
	while (args[count] && ft_no_newline(args[count]))
		count++;
	while (args[count])
	{
		ft_printstr(args[count]);
		if (args[count + 1] != NULL)
			printf(" ");
		count++;
	}
	if (!ft_no_newline(args[1]))
		printf("\n");
}

void	ft_echo(t_cmd *cmd, char *raw_cmd, char *cmd_path, char **arg)
{
	size_t	args_count;

	if (cmd->problem_with_file == 1)
		return ;
	if (ft_no_path(cmd_path, raw_cmd))
		return ;
	args_count = ft_arrlen(arg);
	if (args_count == 1)
		ft_putstr_fd("\n", 1);
	else if (args_count > 2)
		ft_print_arguments(arg);
	if (args_count == 2 && (!ft_no_newline(arg[1]) || arg[1][0] == '\0'))
	{
		ft_printstr(arg[1]);
		printf("\n");
	}
	g_status.exit_status = 0;
}
