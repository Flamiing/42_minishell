/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:40:59 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 12:17:23 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_print_error(char *error_msg)
{
	g_status.exit_status = 1;
	if (!error_msg)
		ft_putstr_fd("minishell: error\n", 2);
	else
		ft_putstr_fd(error_msg, 2);
	return (NULL);
}

void	ft_command_not_found(t_cmd *cmd)
{
	size_t	size;
	char	first_quote[1];

	if (ft_has_variable(cmd->raw_with_var)
		&& ft_not_inside_quotes(cmd->raw_with_var)
		&& cmd->cmd[0] == '\0')
		exit (0);
	else
	{
		first_quote[0] = ft_first_quote(cmd->raw_cmd);
		size = ft_size_without_quotes(cmd->raw_cmd, first_quote[0]);
		cmd->raw_cmd = ft_remove_quotes(cmd->raw_cmd, size, first_quote);
		if (!cmd->raw_cmd)
			exit(1);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->raw_cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
}

void	ft_export_error(char *arg)
{
	ft_putstr_fd(ERROR_EXPORT, 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(arg, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	g_status.exit_status = 1;
}
