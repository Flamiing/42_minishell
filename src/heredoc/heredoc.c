/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:02:52 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/22 11:06:26 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_child_process(t_cmd *cmd, size_t count, char *first_quote,
	size_t size)
{
	rl_catch_signals = 1;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrl_c_heredoc);
	close(g_status.heredoc_fd[0]);
	ft_get_heredoc(cmd, count, first_quote);
	size = ft_strlen(cmd[count].heredoc) + 1;
	write(g_status.heredoc_fd[1], &g_status.eof, sizeof(int));
	write(g_status.heredoc_fd[1], &g_status.sigint, sizeof(int));
	write(g_status.heredoc_fd[1], &size, sizeof(size));
	write(g_status.heredoc_fd[1], cmd[count].heredoc, size * sizeof(char));
	free(cmd[count].heredoc);
	close(g_status.heredoc_fd[1]);
	exit(EXIT_SUCCESS);
}

static void	*ft_parent_process(t_cmd *cmd, size_t count, int status,
	size_t size)
{
	close(g_status.heredoc_fd[1]);
	wait(&status);
	g_status.in_heredoc = 0;
	if (WEXITSTATUS(status) == 1)
	{
		close(g_status.heredoc_fd[0]);
		return (NULL);
	}
	read(g_status.heredoc_fd[0], &g_status.eof, sizeof(int));
	read(g_status.heredoc_fd[0], &g_status.sigint, sizeof(int));
	if (!g_status.sigint && !g_status.eof)
	{
		read(g_status.heredoc_fd[0], &size, sizeof(size));
		cmd[count].heredoc = (char *)malloc(size * sizeof(char));
		if (!cmd[count].heredoc)
			return (NULL);
		read(g_status.heredoc_fd[0], cmd[count].heredoc, size * sizeof(char));
	}
	close(g_status.heredoc_fd[0]);
	return (cmd);
}

static void	*ft_heredoc_process(t_cmd *cmd, size_t count,
	char *first_quote)
{
	pid_t	pid;
	int		status;
	size_t	size;

	size = 0;
	status = 0;
	if (pipe(g_status.heredoc_fd) == -1)
	{
		ft_print_error(ERROR_PIPE);
		g_status.exit_status = 1;
		return (NULL);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_print_error(ERROR_FORK);
		g_status.exit_status = 1;
		return (NULL);
	}
	else if (pid == 0)
		ft_child_process(cmd, count, first_quote, size);
	else
		if (ft_parent_process(cmd, count, status, size) == NULL)
			return (NULL);
	return (cmd);
}

void	*ft_heredoc(t_shell *shell, t_cmd *cmd)
{
	size_t	count;
	char	first_quote[1];

	count = 0;
	while (count < shell->cmd_list_size && g_status.sigint == 0)
	{
		if (cmd[count].type == CMD_HEREDOC)
		{
			g_status.in_heredoc = 1;
			if (!ft_heredoc_process(cmd, count, first_quote))
				return (NULL);
			g_status.in_heredoc = 0;
		}
		count++;
	}
	return (cmd);
}
