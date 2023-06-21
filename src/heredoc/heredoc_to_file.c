/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_to_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:31:53 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/07 16:48:22 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**ft_add_heredoc(char **args, char *filename)
{
	size_t	count;
	size_t	arr_len;
	char	**new_args;

	count = 0;
	arr_len = ft_arrlen(args);
	new_args = (char **)ft_calloc(arr_len + 2, sizeof(char *));
	if (!new_args)
	{
		ft_free_array(args);
		return (ft_print_error(ERROR_MALLOC));
	}
	while (count < arr_len)
	{
		new_args[count] = args[count];
		count++;
	}
	new_args[count] = filename;
	free(args);
	return (new_args);
}

static char	**ft_no_heredoc(t_shell *shell, t_cmd *cmd, size_t count)
{
	int		file;
	char	**args;
	char	*filename;
	char	*temp;

	temp = ft_itoa(count);
	if (!temp)
		return (NULL);
	filename = ft_strjoin(shell->minishell_heredoc_dir, temp);
	free(temp);
	if (!filename)
		return (NULL);
	file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	write(file, "", 0);
	close(file);
	cmd->heredoc_filename = filename;
	args = ft_add_heredoc(cmd->args, filename);
	if (!args)
		return (NULL);
	return (args);
}

char	**ft_heredoc_to_file(t_shell *shell, t_cmd *cmd, char *heredoc,
	size_t count)
{
	int		file;
	char	**args;
	char	*filename;
	char	*temp;
	size_t	size;

	if (!heredoc)
		return (ft_no_heredoc(shell, cmd, count));
	size = ft_strlen(heredoc);
	temp = ft_itoa(count);
	if (!temp)
		return (NULL);
	filename = ft_strjoin(shell->minishell_heredoc_dir, temp);
	free(temp);
	if (!filename)
		return (NULL);
	file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	write(file, heredoc, size);
	close(file);
	cmd->heredoc_filename = filename;
	args = ft_add_heredoc(cmd->args, filename);
	if (!args)
		return (NULL);
	return (args);
}
