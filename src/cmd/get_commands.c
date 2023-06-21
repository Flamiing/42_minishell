/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:55:32 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/10 12:56:21 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_is_built_in(char *cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	if ((ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0 && len == 4)
		|| (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0 && len == 2)
		|| (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0 && len == 3)
		|| (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0 && len == 6)
		|| (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0 && len == 5)
		|| (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0 && len == 3)
		|| (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0 && len == 4))
		return (CMD_BUILT_IN);
	else
		return (CMD_NOT_BUILT_IN);
}

static int	ft_get_type(t_token *token, char *cmd)
{
	if (ft_is_built_in(cmd) == CMD_BUILT_IN)
		return (CMD_BUILT_IN);
	else if (token->type == TYPE_HEREDOC)
		return (CMD_HEREDOC);
	else if (token->type == TYPE_APPEND)
		return (CMD_APPEND);
	else if (token->type == TYPE_INPUT)
		return (CMD_INPUT);
	else if (token->type == TYPE_OUTPUT)
		return (CMD_OUTPUT);
	else if (token->type == TYPE_PIPE)
		return (CMD_PIPE);
	else
		return (CMD_NOT_BUILT_IN);
}

static t_cmd	*ft_get_cmd(t_shell *shell, t_token *token, t_cmd *cmd)
{
	cmd->raw_cmd = ft_parse_cmd(cmd, shell->env, token->data);
	cmd->cmd = ft_to_lower(cmd->raw_cmd);
	if (!cmd->cmd)
		return (NULL);
	if (token->type == TYPE_CMD && ft_has_quotes(cmd->cmd) == 0)
	{
		cmd->cmd_path = ft_get_path(shell->env, cmd->cmd);
		if (!cmd->cmd_path)
			return (NULL);
	}
	else
		cmd->cmd_path = ft_strdup(cmd->cmd);
	cmd->args = ft_get_args(cmd->cmd_path, shell->env, token);
	cmd->raw_args = ft_get_raw_args(cmd->cmd_path, token);
	if (!cmd->args || !cmd->raw_args)
		return (NULL);
	cmd->type = ft_get_type(token, cmd->cmd);
	cmd->heredoc = NULL;
	cmd->heredoc_filename = NULL;
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->can_remove_quotes = 1;
	if (cmd->type == CMD_BUILT_IN)
		cmd->can_remove_quotes = 0;
	return (cmd);
}

static int	ft_is_cmd(int type)
{
	if (type == TYPE_CMD
		|| type == TYPE_VAR
		|| type == TYPE_HEREDOC
		|| type == TYPE_APPEND
		|| type == TYPE_INPUT
		|| type == TYPE_OUTPUT
		|| type == TYPE_PIPE)
		return (1);
	else
		return (0);
}

void	*ft_get_commands(t_shell *shell, t_token **tokens)
{
	t_token	*token;
	size_t	count;

	token = *tokens;
	shell->cmd = (t_cmd *)ft_calloc(shell->cmd_list_size + 1, sizeof(t_cmd));
	if (!shell->cmd)
		return (ft_print_error(ERROR_MALLOC));
	count = 0;
	while (token != NULL)
	{
		if (ft_is_cmd(token->type))
		{
			if (ft_get_cmd(shell, token, &shell->cmd[count]) == NULL)
			{
				free(shell->cmd);
				return (NULL);
			}
			count++;
		}
		token = token->next;
	}
	if (ft_remove_cmd_quotes(shell, shell->cmd) == QUOTE_REMOVE_ERROR
		|| ft_remove_args_quotes(shell, shell->cmd) == QUOTE_REMOVE_ERROR)
		return (NULL);
	return (shell);
}
