/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:07:43 by alaaouam          #+#    #+#             */
/*   Updated: 2023/05/25 19:18:41 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_append(char *heredoc, char *line)
{
	char	*new_heredoc;
	char	*temp;

	if (!heredoc)
	{
		heredoc = ft_strjoin(line, "\n");
		free(line);
	}
	else
	{
		temp = ft_strjoin(heredoc, line);
		free(heredoc);
		free(line);
		if (!temp)
			return (NULL);
		new_heredoc = ft_strjoin(temp, "\n");
		free(temp);
		if (!new_heredoc)
		{
			heredoc = NULL;
			return (NULL);
		}
		heredoc = new_heredoc;
	}
	return (heredoc);
}

void	ft_clean_heredoc(t_cmd *cmd)
{
	if (cmd->heredoc)
	{
		free(cmd->heredoc);
		cmd->heredoc = NULL;
	}
}

int	ft_heredoc_reader(t_cmd *cmd, char *delimiter)
{
	char	*line;
	size_t	delimiter_size;

	delimiter_size = ft_strlen(delimiter);
	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
			return (ft_ctrl_d_heredoc());
		if (ft_strncmp(line, delimiter, delimiter_size) == 0
			&& ft_strlen(line) == delimiter_size)
		{
			free(line);
			break ;
		}
		else
		{
			cmd->heredoc = ft_append(cmd->heredoc, line);
			if (!cmd->heredoc)
				return (2);
		}
	}
	return (0);
}

void	*ft_get_heredoc(t_cmd *cmd, size_t count, char *first_quote)
{
	char	*delimiter;

	first_quote[0] = ft_first_quote(cmd[count].args[0]);
	delimiter = ft_strtrim(cmd[count].args[1], first_quote);
	if (!delimiter)
		return (NULL);
	if (ft_heredoc_reader(cmd + count, delimiter) == 1)
		ft_clean_heredoc(cmd + count);
	free(delimiter);
	return (cmd);
}
