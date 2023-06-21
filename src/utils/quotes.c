/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:44:18 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/08 15:19:13 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	ft_first_quote(char *str)
{
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count])
	{
		if (str[count] == SINGLE_QUOTE || str[count] == DOUBLE_QUOTE)
			return (str[count]);
		count++;
	}
	return (0);
}

int	ft_has_quotes(char *str)
{
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count])
	{
		if (str[count] == SINGLE_QUOTE || str[count] == DOUBLE_QUOTE)
			return (1);
		count++;
	}
	return (0);
}

int	ft_remove_cmd_quotes(t_shell *shell, t_cmd *cmd)
{
	size_t	count;
	size_t	size;
	char	first_quote[1];

	count = 0;
	while (count < shell->cmd_count)
	{
		if (ft_has_quotes(cmd[count].cmd))
		{
			first_quote[0] = ft_first_quote(cmd[count].cmd);
			size = ft_size_without_quotes(cmd[count].cmd, first_quote[0]);
			cmd[count].cmd = ft_remove_quotes(cmd[count].cmd,
					size, first_quote);
			if (!cmd[count].cmd)
				return (QUOTE_REMOVE_ERROR);
			cmd[count].cmd_path = ft_get_path(shell->env, cmd[count].cmd);
			if (!cmd->cmd_path)
				return (QUOTE_REMOVE_ERROR);
		}
		count++;
	}
	return (0);
}

int	ft_clean_argument(t_cmd *cmd, size_t pos)
{
	char	first_quote[1];
	size_t	size;

	if (ft_has_quotes(cmd->args[pos])
		&& ft_remove_quotes_valid(cmd->cmd, cmd->can_remove_quotes, cmd->type))
	{
		first_quote[0] = ft_first_quote(cmd->args[pos]);
		size = ft_size_without_quotes(cmd->args[pos], first_quote[0]);
		cmd->args[pos] = ft_remove_quotes(cmd->args[pos], size, first_quote);
		if (!cmd->args[pos])
			return (QUOTE_REMOVE_ERROR);
	}
	return (0);
}

int	ft_remove_args_quotes(t_shell *shell, t_cmd *cmd)
{
	size_t	count;
	size_t	pos;

	count = 0;
	while (count < shell->cmd_count)
	{
		pos = 0;
		while (cmd[count].args[pos])
		{
			if (ft_clean_argument(cmd + count, pos) == QUOTE_REMOVE_ERROR)
				return (QUOTE_REMOVE_ERROR);
			pos++;
		}
		count++;
	}
	return (0);
}
