/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:48:52 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/21 15:26:08 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_handle_waits(pid_t *pid, size_t size)
{
	size_t	count;
	int		status;

	count = 0;
	while (count <= size)
	{
		if (pid[count] == -1)
		{
			g_status.exit_status = 1;
			return ;
		}
		count++;
	}
	count = 0;
	while (count <= size)
	{
		if (pid[count] > 0)
		{
			waitpid(pid[count], &status, 0);
			if (WIFEXITED(status))
				g_status.exit_status = WEXITSTATUS(status);
		}
		count++;
	}
}

static void	*ft_execute_cmds(t_shell *shell, t_cmd *cmd)
{
	size_t	size;

	size = shell->cmd_count;
	shell->pid = (pid_t *)ft_calloc(size + 1, sizeof(pid_t));
	if (!shell->pid)
		return (ft_print_error(ERROR_MALLOC));
	if (ft_process(shell, cmd, shell->pid) == NULL)
		return (NULL);
	ft_handle_waits(shell->pid, size);
	free(shell->pid);
	return (NULL);
}

int	ft_execute(t_shell *shell, t_cmd *cmd)
{
	if (shell->heredoc_count > 0)
	{
		if (ft_heredoc(shell, cmd) == NULL)
		{
			g_status.exit_status = 1;
			return (HEREDOC_ERROR);
		}
	}
	ft_cmd_expansion(shell, cmd);
	ft_execute_cmds(shell, cmd);
	ft_read_env(shell);
	unlink(shell->minishell_env_dir);
	if (g_status.cd_status != -1)
		g_status.exit_status = g_status.cd_status;
	if (g_status.file_is_folder == 1 && shell->cmd_count == 1)
		g_status.exit_status = 1;
	g_status.cd_status = -1;
	g_status.infile_problem = 0;
	return (0);
}
