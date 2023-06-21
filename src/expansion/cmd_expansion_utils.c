/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:12:28 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 12:05:35 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_valid_to_remove_quotes(t_cmd *cmd)
{
	size_t	len;

	len = ft_strlen(cmd->cmd);
	if (((ft_strncmp(cmd->cmd, "echo", ft_strlen(cmd->cmd)) == 0 && len == 4)
			|| (ft_strncmp(cmd->cmd, "cd",
					ft_strlen(cmd->cmd)) == 0 && len == 2)
			|| (ft_strncmp(cmd->cmd, "pwd",
					ft_strlen(cmd->cmd)) == 0 && len == 3)
			|| (ft_strncmp(cmd->cmd, "export",
					ft_strlen(cmd->cmd)) == 0 && len == 6)
			|| (ft_strncmp(cmd->cmd, "unset",
					ft_strlen(cmd->cmd)) == 0 && len == 5)
			|| (ft_strncmp(cmd->cmd, "env",
					ft_strlen(cmd->cmd)) == 0 && len == 3)))
	{
		cmd->can_remove_quotes = 1;
		return (1);
	}
	else
		return (0);
}

t_cmd	*ft_expand_cmd_with_var(t_shell *shell, t_cmd *cmd)
{
	size_t	count;

	count = 0;
	while (count < shell->cmd_list_size)
	{
		if (ft_has_variable(cmd[count].raw_with_var)
			&& ft_not_inside_quotes(cmd[count].raw_with_var))
		{
			if (cmd[count].type == TYPE_CMD)
				if (ft_expand_cmd(shell, cmd + count) == NULL)
					return (NULL);
			if (cmd[count].type == TYPE_ARG)
				if (ft_expand_args(cmd + count) == NULL)
					return (NULL);
		}
		count++;
	}
	return (cmd);
}

t_cmd	*ft_expand_args_with_var(t_shell *shell, t_cmd *cmd)
{
	size_t	count;

	count = 0;
	while (count < shell->cmd_list_size)
	{
		if (ft_expand_args(cmd + count) == NULL)
			return (NULL);
		count++;
	}
	return (cmd);
}

static int	ft_variable_alone(char *str)
{
	size_t	count;

	if (!str)
		return (0);
	if (str[0] != '$')
		return (0);
	count = 0;
	while (str[count])
	{
		if (str[count] == ' ' || (str[count] > 8 && str[count] <= 13)
			|| str[count] == SINGLE_QUOTE || str[count] == DOUBLE_QUOTE)
			return (0);
		count++;
	}
	return (1);
}

size_t	ft_need_expansion(char *raw, char *clean)
{
	if (ft_has_variable(raw)
		&& ft_not_inside_quotes(raw)
		&& ft_variable_alone(raw)
		&& clean[0] != '\0')
		return (1);
	else
		return (0);
}
