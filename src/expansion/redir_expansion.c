/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:46:12 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 12:04:02 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_cmd	*ft_output_expand_1(t_shell *shell, t_cmd *cmd, size_t *count,
	size_t pos)
{
	int	file;

	while (pos < (shell->cmd_list_size - 1) && (cmd[pos].type == CMD_OUTPUT
			|| cmd[pos].type == CMD_APPEND)
		&& (cmd[pos + 1].type == CMD_OUTPUT
			|| cmd[pos + 1].type == CMD_APPEND))
	{
		if (ft_is_a_folder(cmd[pos].args[1], cmd + (*count - 1)))
			return (NULL);
		file = ft_open_file(cmd + pos, cmd[pos].args[1], cmd[pos].type);
		if (pos == (shell->cmd_list_size - 1) && file > -1)
			close(file);
		pos++;
	}
	cmd[*count - 1].args = ft_add_args(cmd + (*count - 1), cmd[pos].args + 2);
	cmd[*count - 1].outfile = ft_open_file(cmd + *count - 1, cmd[pos].args[1],
			cmd[pos].type);
	if (file == -1)
	{
		close(cmd[*count - 1].outfile);
		cmd[*count - 1].outfile = -1;
	}
	*count += pos - 1;
	return (cmd);
}

static t_cmd	*ft_output_expand_2(t_shell *shell, t_cmd *cmd, size_t *count,
	size_t pos)
{
	int	file;

	while (pos < (shell->cmd_list_size - 1) && (cmd[pos].type == CMD_OUTPUT
			|| cmd[pos].type == CMD_APPEND) && (cmd[pos + 1].type == CMD_OUTPUT
			|| cmd[pos + 1].type == CMD_APPEND))
	{
		if (ft_is_a_folder(cmd[pos].args[1], cmd + (*count + 1)))
			return (NULL);
		file = ft_open_file(cmd + pos, cmd[pos].args[1], cmd[pos].type);
		if (pos == (shell->cmd_list_size - 1) && file > -1)
			close(file);
		pos++;
	}
	cmd[*count + 1].outfile = ft_open_file(cmd + *count + 1, cmd[pos].args[1],
			cmd[*count].type);
	if (file == -1)
	{
		close(cmd[*count + 1].outfile);
		cmd[*count + 1].outfile = -1;
	}
	*count += pos;
	return (cmd);
}

static t_cmd	*ft_output_expansion(t_shell *shell, t_cmd *cmd, size_t *count,
	size_t pos)
{
	if (*count > 0)
	{
		if (ft_output_expand_1(shell, cmd, count, pos) == NULL)
			return (NULL);
	}
	else
	{
		if (ft_output_expand_2(shell, cmd, count, pos) == NULL)
			return (NULL);
	}
	return (cmd);
}

static void	ft_redir_fds(t_shell *shell, t_cmd *cmd, size_t count)
{
	if (count < (shell->cmd_list_size - 1))
	{
		cmd[count + 1].infile = ft_open_file(cmd + count + 1,
				cmd[count].args[1], cmd[count].type);
		if (count > 0)
		{
			cmd[count - 1].problem_with_file = cmd[count + 1].problem_with_file;
			cmd[count - 1].infile = dup(cmd[count + 1].infile);
		}
		if (cmd[count + 1].infile == -1)
			g_status.infile_problem = 1;
	}
	else
	{
		cmd[count].infile = ft_open_file(cmd + count, cmd[count].args[1],
				cmd[count].type);
		if (count > 0)
		{
			cmd[count - 1].problem_with_file = cmd[count].problem_with_file;
			cmd[count - 1].infile = dup(cmd[count].infile);
		}
		if (cmd[count].infile == -1)
			g_status.infile_problem = 1;
	}
}

t_cmd	*ft_redir_expansion(t_shell *shell, t_cmd *cmd)
{
	size_t	count;
	size_t	pos;

	count = 0;
	while (count < shell->cmd_list_size && g_status.infile_problem != 1)
	{
		pos = count;
		if (cmd[count].type == CMD_INPUT)
			ft_redir_fds(shell, cmd, count);
		if (cmd[count].type == CMD_OUTPUT || cmd[count].type == CMD_APPEND)
			if (ft_output_expansion(shell, cmd, &count, pos) == NULL)
				return (NULL);
		count++;
	}
	if (count == 1 && (cmd[0].type == CMD_OUTPUT || cmd[0].type == CMD_APPEND))
	{
		cmd[0].outfile = ft_open_file(cmd, cmd[0].args[1], cmd[0].type);
		close(cmd[0].outfile);
	}
	return (cmd);
}
