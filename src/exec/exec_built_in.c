/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:10:16 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/27 19:43:09 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_wrong_exit_cmd(char *raw_cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(raw_cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
	g_status.exit_status = 127;
}

void	ft_built_in_out(t_shell *shell, t_cmd *cmd, char **args)
{
	size_t	len;

	len = ft_strlen(cmd->cmd);
	if (ft_strncmp(cmd->cmd, "unset", len) == 0 && len == 5)
		ft_unset(shell, args);
	else if (ft_strncmp(cmd->cmd, "cd", len) == 0 && len == 2
		&& shell->pipe_count == 0)
		ft_cd(shell, args);
}

void	ft_exec_built_in(t_shell *shell, t_cmd *cmd, char **args, char **env)
{
	size_t	len;

	len = ft_strlen(cmd->cmd);
	if (ft_strncmp(cmd->cmd, "echo", len) == 0 && len == 4)
		ft_echo(cmd, cmd->raw_cmd, cmd->cmd_path, args);
	else if (ft_strncmp(cmd->cmd, "export", len) == 0 && len == 6)
		ft_export(shell, args + 1);
	else if (ft_strncmp(cmd->cmd, "pwd", len) == 0 && len == 3)
		ft_pwd(args);
	else if (ft_strncmp(cmd->cmd, "env", len) == 0 && len == 3)
		ft_env(env);
}
