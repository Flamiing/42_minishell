/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:37:07 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/27 19:29:36 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_ctrl_d(t_shell *shell)
{
	g_status.eof = 1;
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 6);
	free(shell->minishell_env_dir);
	free(shell->minishell_heredoc_dir);
	if (shell->env)
		ft_free_array(shell->env);
	exit(g_status.exit_status);
}

int	ft_ctrl_d_heredoc(void)
{
	if (g_status.sigint == 0)
	{
		g_status.eof = 1;
		printf("\033[%dD", 1);
		printf("\033[1X");
	}
	write(g_status.heredoc_fd[1], &g_status.eof, sizeof(int));
	write(g_status.heredoc_fd[1], &g_status.sigint, sizeof(int));
	close(g_status.heredoc_fd[0]);
	close(g_status.heredoc_fd[1]);
	exit (EXIT_SUCCESS);
}

static void	ft_ctrl_c_and_sigquit(int signal)
{
	g_status.exit_status = 1;
	if (signal == SIGINT && !g_status.in_heredoc)
	{
		g_status.exit_status = 1;
		ft_putstr_fd("\n", STDOUT);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_status.cmd_execution != 1)
			rl_redisplay();
	}
	else if (signal == SIGQUIT && !g_status.in_heredoc)
	{
		if (g_status.cmd_execution == 1)
		{
			g_status.exit_status = 131;
			printf("Quit: 3\n");
		}
	}
}

void	ft_ctrl_c_heredoc(int signal)
{
	(void)signal;
	if (signal == SIGINT && g_status.in_heredoc)
	{
		write(g_status.heredoc_fd[1], &g_status.eof, sizeof(int));
		write(g_status.heredoc_fd[1], &g_status.sigint, sizeof(int));
		close(g_status.heredoc_fd[0]);
		close(g_status.heredoc_fd[1]);
		g_status.sigint = 1;
		ft_putstr_fd("\n", STDOUT);
		rl_done = 1;
		exit(EXIT_FAILURE);
	}
}

void	ft_handle_signals(void)
{
	signal(SIGQUIT, ft_ctrl_c_and_sigquit);
	signal(SIGINT, ft_ctrl_c_and_sigquit);
}
