/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:08:15 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/22 11:03:36 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_wrong_exit_argument(t_cmd *cmd)
{
	ft_clean_argument(cmd, 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_status.exit_status = 255;
}

static void	ft_too_many_args(void)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd("too many arguments\n", 2);
	g_status.exit_status = 1;
}

static int	ft_invalid_simbols(char *arg)
{
	size_t	count;
	size_t	sign_count;

	count = 0;
	sign_count = 0;
	while (arg[count])
	{
		if (arg[count] == '-' || arg[count] == '+')
		{
			sign_count++;
			if (!ft_isdigit(arg[count + 1]))
				return (1);
		}
		count++;
	}
	if (sign_count > 1)
		return (1);
	else
		return (0);
}

static int	ft_invalid(char *arg)
{
	size_t	count;

	if (!arg)
		return (1);
	if (ft_max_or_min_nbr(arg))
		return (1);
	if (ft_invalid_simbols(arg))
		return (1);
	count = 0;
	while (arg[count])
	{
		if (!ft_isdigit(arg[count]) && arg[count] != '-' && arg[count] != '+'
			&& arg[count] != ' ' && (arg[count] <= 8 || arg[count] > 13))
			return (1);
		count++;
	}
	return (0);
}

void	ft_exit(t_shell *shell, t_cmd *cmd, char **args)
{
	size_t	args_count;
	size_t	exit_status;

	args_count = ft_arrlen(args);
	cmd->can_remove_quotes = 1;
	ft_putstr_fd("exit\n", 2);
	if (args_count == 1)
		ft_exit_and_free(g_status.exit_status, shell);
	else if (args_count > 1)
	{
		if (!ft_is_empty_with_quotes(args[1]))
			ft_clean_argument(cmd, 1);
		if (ft_invalid(args[1]))
		{
			ft_wrong_exit_argument(cmd);
			ft_exit_and_free(g_status.exit_status, shell);
		}
		else if (args_count > 2)
		{
			ft_too_many_args();
			return ;
		}
		exit_status = ft_atoi(args[1]);
		ft_exit_and_free(exit_status, shell);
	}
}
