/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:12:17 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 11:43:27 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**ft_get_expanded_args(char **args, char *raw_args, char *cmd_path)
{
	char	**new_args;
	char	**raw;
	size_t	size;
	size_t	count;

	raw = ft_split(raw_args, ' ');
	size = ft_arrlen(args) + ft_arrlen(raw);
	new_args = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!raw_args)
	{
		ft_free_array(args);
		return (ft_print_error(ERROR_MALLOC));
	}
	count = 0;
	new_args[count] = ft_strdup(cmd_path);
	count++;
	while (count < size)
	{
		new_args[count] = raw[count - 1];
		count++;
	}
	free(args[0]);
	free(args);
	free(raw);
	return (new_args);
}

static char	*ft_only_cmd(char *raw_cmd)
{
	char	*cmd;
	size_t	count;
	size_t	size;

	count = 0;
	size = ft_strlen_x(raw_cmd, ' ');
	cmd = (char *)ft_calloc(size + 1, sizeof(char));
	if (!cmd)
		return (ft_print_error(ERROR_MALLOC));
	while (raw_cmd[count])
	{
		if (raw_cmd[count] == ' '
			|| (raw_cmd[count] > 8 && raw_cmd[count] <= 13))
			break ;
		cmd[count] = raw_cmd[count];
		count++;
	}
	return (cmd);
}

t_cmd	*ft_expand_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*raw;

	if (cmd->cmd[0] == '\0')
		return (cmd);
	raw = cmd->cmd;
	cmd->cmd = ft_only_cmd(cmd->cmd);
	if (!cmd->cmd)
	{
		free(raw);
		return (NULL);
	}
	cmd->cmd_path = ft_get_path(shell->env, cmd->cmd);
	if (!cmd->cmd_path)
	{
		free(raw);
		return (NULL);
	}
	cmd->args = ft_get_expanded_args(cmd->args, raw + ft_strlen(cmd->cmd),
			cmd->cmd_path);
	free(raw);
	if (!cmd->args)
		return (NULL);
	return (cmd);
}
