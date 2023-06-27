/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:47:12 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/27 19:42:35 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_close_pipes(t_shell *shell, size_t pos, size_t size)
{
	if (pos > START)
	{
		close(shell->old_fds[0]);
		close(shell->old_fds[1]);
	}
	if (pos < (size - 1))
	{
		shell->old_fds[0] = shell->new_fds[0];
		shell->old_fds[1] = shell->new_fds[1];
	}
}

pid_t	ft_process_cmd(t_shell *shell, t_cmd *cmd, size_t pos)
{
	pid_t	pid;
	size_t	size;

	size = shell->cmd_count;
	pid = fork();
	if (pid == -1)
		ft_print_error(ERROR_FORK);
	else if (pid == 0)
	{
		ft_handle_fds(shell, cmd, pos);
		if (cmd->problem_with_file == 1
			|| (g_status.infile_problem == 1 && shell->pipe_count == 0))
			exit(EXIT_FAILURE);
		if (execve(cmd->cmd_path, cmd->args, shell->env) == -1)
		{
			g_status.exit_status = 127;
			ft_command_not_found(cmd);
			exit(127);
		}
	}
	ft_close_pipes(shell, pos, size);
	return (pid);
}

void	ft_child_process(t_shell *shell, t_cmd *cmd, int *infofd, size_t pos)
{
	ft_handle_fds(shell, cmd, pos);
	close(infofd[1]);
	read(infofd[0], &g_status.exit_status, sizeof(int));
	close(infofd[0]);
	if (cmd->problem_with_file == 1
		|| (g_status.infile_problem == 1 && shell->pipe_count == 0))
		exit(EXIT_FAILURE);
	ft_exec_built_in(shell, cmd, cmd->args, shell->env);
	exit(g_status.exit_status);
}

static int	ft_check_exit(t_shell *shell, t_cmd *cmd, char **args)
{
	size_t	len;

	len = ft_strlen(cmd->cmd);
	if (ft_strncmp(cmd->cmd, "exit", len) == 0 && len == 4
		&& shell->pipe_count == 0)
	{
		if (ft_is_lowercase(cmd->raw_cmd))
			ft_exit(shell, cmd, args);
		else
			ft_wrong_exit_cmd(cmd->raw_cmd);
	}
	return (0);
}

pid_t	ft_process_built_in(t_shell *shell, t_cmd *cmd, size_t pos)
{
	pid_t	pid;
	size_t	size;
	int		infofd[2];

	size = shell->cmd_count;
	ft_check_exit(shell, cmd, cmd->args);
	if (pipe(infofd) == -1)
	{
		ft_print_error(ERROR_PIPE);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
		ft_print_error(ERROR_FORK);
	else if (pid == 0)
		ft_child_process(shell, cmd, infofd, pos);
	ft_built_in_out(shell, cmd, cmd->args);
	close(infofd[0]);
	write(infofd[1], &g_status.exit_status, sizeof(int));
	close(infofd[1]);
	ft_close_pipes(shell, pos, size);
	return (pid);
}
