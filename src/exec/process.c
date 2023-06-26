/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:13:53 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/26 12:50:49 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static pid_t	ft_handle_cmd(t_shell *shell, size_t count, size_t *pos)
{
	pid_t	pid;

	pid = -2;
	if (shell->cmd[count].type == CMD_NOT_BUILT_IN)
	{
		pid = ft_process_cmd(shell, shell->cmd + count, *pos);
		*pos += 1;
	}
	return (pid);
}

static pid_t	ft_handle_built_in(t_shell *shell, size_t count, size_t *pos)
{
	pid_t	pid;

	pid = -2;
	if (shell->cmd[count].type == CMD_BUILT_IN)
	{
		pid = ft_process_built_in(shell, shell->cmd + count, *pos);
		*pos += 1;
	}
	return (pid);
}

static pid_t	*ft_process_loop(t_shell *shell, t_cmd *cmd, size_t *count,
	size_t *pos)
{
	if (cmd[*count].type != CMD_BUILT_IN
		&& cmd[*count].type != CMD_NOT_BUILT_IN)
		return (shell->pid);
	if (*pos <= (shell->cmd_count - 1))
	{
		if (pipe(shell->new_fds) == -1)
			return (ft_print_error(ERROR_PIPE));
	}
	if (cmd[*count].type == CMD_NOT_BUILT_IN)
		shell->pid[*pos] = ft_handle_cmd(shell, *count, pos);
	else if (cmd[*count].type == CMD_BUILT_IN)
		shell->pid[*pos] = ft_handle_built_in(shell, *count, pos);
	if (shell->pid[*pos] == -2)
		return (NULL);
	return (shell->pid);
}

static void	ft_close_file_descriptors(t_shell *shell, size_t pos)
{
	if (pos > 1)
	{
		close(shell->old_fds[0]);
		close(shell->old_fds[1]);
	}
	close(shell->new_fds[0]);
	close(shell->new_fds[1]);
}

pid_t	*ft_process(t_shell *shell, t_cmd *cmd, pid_t *pid)
{
	size_t	count;
	size_t	pos;

	count = 0;
	pos = 0;
	while (count < shell->cmd_list_size)
	{
		if (cmd[count].type != CMD_HEREDOC && cmd[count].type != CMD_PIPE)
		{
			while (count < shell->cmd_list_size - 1
				&& cmd[count].type == CMD_OUTPUT
				&& cmd[count + 1].type == CMD_OUTPUT)
				count++;
			if (ft_process_loop(shell, cmd, &count, &pos) == NULL)
				return (NULL);
		}
		count++;
	}
	ft_close_file_descriptors(shell, pos);
	return (pid);
}
