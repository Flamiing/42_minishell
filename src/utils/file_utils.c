/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 03:07:17 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/23 11:54:37 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_check_access(char *filename)
{
	int	fd;

	fd = access(filename, R_OK);
	if (fd == -1)
	{
		g_status.exit_status = errno;
		return (-1);
	}
	return (0);
}

static int	ft_file_not_found(t_cmd *cmd, char *filename, int file)
{
	struct stat	path_stat;

	ft_putstr_fd("minishell: ", 2);
	perror(filename);
	if (file > -1)
		close(file);
	cmd->problem_with_file = 1;
	g_status.file_is_folder = 1;
	g_status.exit_status = 1;
	if (stat(filename, &path_stat) == 0)
		if (S_ISDIR(path_stat.st_mode))
			return (-2);
	return (-1);
}

int	ft_is_a_folder(char *path, t_cmd *cmd)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			g_status.file_is_folder = 1;
			cmd->problem_with_file = 1;
			g_status.exit_status = 1;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("Is a directory\n", 2);
			return (1);
		}
	}
	return (0);
}

int	ft_open_file(t_cmd *cmd, char *filename, int type)
{
	int	file;

	file = -1;
	if (type == CMD_INPUT)
	{
		if (ft_check_access(filename) == -1)
			return (ft_file_not_found(cmd, filename, file));
		file = open(filename, O_RDONLY);
		if (file == -1)
			return (ft_file_not_found(cmd, filename, file));
	}
	else if (type == CMD_OUTPUT)
	{
		file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file == -1 || access(filename, W_OK) != 0)
			return (ft_file_not_found(cmd, filename, file));
	}
	else
	{
		file = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (file == -1 || access(filename, W_OK) != 0)
			return (ft_file_not_found(cmd, filename, file));
	}
	return (file);
}

size_t	ft_file_size(char *filename)
{
	ssize_t	count;
	char	*line;
	int		file;

	file = open(filename, O_RDONLY);
	if (file == -1)
		return (0);
	count = 0;
	line = get_next_line(file);
	while (line)
	{
		free(line);
		line = get_next_line(file);
		count++;
	}
	close(file);
	return (count);
}
