/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 02:57:08 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/21 21:34:50 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_first_redirection(t_shell *shell, t_cmd *cmd, size_t pos)
{
	if (cmd->infile != -1)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	else if (pos > START)
	{
		dup2(shell->old_fds[0], STDIN_FILENO);
		close(shell->old_fds[0]);
		close(shell->old_fds[1]);
	}
}

static void	ft_seccond_redirection(t_shell *shell, t_cmd *cmd,
	size_t size, size_t pos)
{
	if (cmd->outfile != -1 && cmd->outfile != -2)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	else if (pos < size - 1 || ((cmd + 1) && (cmd + 1)->type == CMD_PIPE))
	{
		close(shell->new_fds[0]);
		dup2(shell->new_fds[1], STDOUT_FILENO);
		close(shell->new_fds[1]);
	}
}

void	ft_handle_fds(t_shell *shell, t_cmd *cmd, size_t pos)
{
	size_t	size;

	size = shell->cmd_count;
		ft_first_redirection(shell, cmd, pos);
	if (pos <= size - 1)
		ft_seccond_redirection(shell, cmd, size, pos);
}
