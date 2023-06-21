/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:11:39 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/21 17:23:25 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_cmd	*ft_heredoc_expansion(t_shell *shell, t_cmd *cmd)
{
	size_t	count;
	size_t	pos;

	count = 0;
	pos = 0;
	while (count < shell->cmd_list_size)
	{
		pos = count + 1;
		if (cmd[count].type != CMD_HEREDOC)
		{
			if (pos < shell->cmd_list_size && cmd[pos].type == CMD_HEREDOC)
			{
				while (cmd[pos + 1].type == CMD_HEREDOC)
					pos++;
				cmd[count].args = ft_heredoc_to_file(shell, cmd + count,
						cmd[pos].heredoc, count);
				if (!cmd[count].args)
					return (NULL);
			}
		}
		count++;
	}
	return (cmd);
}

static t_cmd	*ft_remove_built_in_quotes(t_shell *shell, t_cmd *cmd)
{
	size_t	count;
	size_t	pos;

	count = 0;
	while (count < shell->cmd_list_size)
	{
		if (ft_valid_to_remove_quotes(cmd + count)
			|| cmd[count].type != CMD_BUILT_IN)
		{
			pos = 0;
			while (cmd[count].args[pos])
			{
				ft_clean_argument(cmd + count, pos);
				pos++;
			}
		}
		count++;
	}
	return (cmd);
}

t_cmd	*ft_cmd_expansion(t_shell *shell, t_cmd *cmd)
{
	if (ft_heredoc_expansion(shell, cmd) == NULL)
		return (NULL);
	if (ft_remove_built_in_quotes(shell, cmd) == NULL)
		return (NULL);
	if (ft_redir_expansion(shell, cmd) == NULL)
		return (NULL);
	if (ft_expand_cmd_with_var(shell, cmd) == NULL)
		return (NULL);
	if (ft_expand_args_with_var(shell, cmd) == NULL)
		return (NULL);
	return (cmd);
}
