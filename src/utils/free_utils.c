/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:41:58 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/26 12:14:06 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_array(char **arr)
{
	int	count;

	count = 0;
	if (!arr)
		return ;
	while (arr[count])
	{
		free(arr[count]);
		count++;
	}
	free(arr[count]);
	free(arr);
}

void	*ft_free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens)
		return (NULL);
	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	*tokens = NULL;
	return (NULL);
}

static void	ft_free_cmds(t_cmd *cmd, size_t size)
{
	size_t	count;

	count = 0;
	while (count < size)
	{
		if (cmd[count].cmd)
			free(cmd[count].cmd);
		if (cmd[count].raw_cmd)
			free(cmd[count].raw_cmd);
		if (cmd[count].raw_with_var)
			free(cmd[count].raw_with_var);
		if (cmd[count].cmd_path)
			free(cmd[count].cmd_path);
		if (cmd[count].heredoc_filename)
			unlink(cmd[count].heredoc_filename);
		if (cmd[count].args)
			ft_free_array(cmd[count].args);
		if (cmd[count].raw_args)
			ft_free_array(cmd[count].raw_args);
		if (cmd[count].heredoc)
			free(cmd[count].heredoc);
		count++;
	}
	free(cmd);
	cmd = NULL;
}

void	*ft_free_everything(t_shell *shell)
{
	if (shell->tokens)
		ft_free_tokens(&shell->tokens);
	if (shell->cmd && shell->parser_status == 0)
	{
		ft_close_files(shell->cmd, shell->cmd_count + shell->redir_count
			+ shell->heredoc_count);
		ft_free_cmds(shell->cmd, shell->cmd_count + shell->redir_count
			+ shell->heredoc_count);
	}
	return (NULL);
}

void	ft_destroy_shell(t_shell *shell)
{
	free(shell->minishell_env_dir);
	free(shell->minishell_heredoc_dir);
	ft_free_everything(shell);
	if (shell->env)
		ft_free_array(shell->env);
}
