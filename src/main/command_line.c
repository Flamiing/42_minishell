/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:02:15 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 12:44:49 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	ft_has_input(char *buffer)
{
	size_t	count;

	if (buffer[0] == '\0')
		return (0);
	count = 0;
	while (buffer[count])
	{
		if (buffer[count] != ' ' && (buffer[count] < 8 || buffer[count] > 13))
			return (1);
		count++;
	}
	return (0);
}

static int	ft_handle_command_line(t_shell *shell)
{
	add_history(shell->buffer);
	shell->tokens = ft_lexer(shell->buffer, shell);
	if (!shell->tokens)
	{
		free(shell->buffer);
		exit(EXIT_FAILURE);
	}
	if (ft_parser(shell, &shell->tokens) != SYNTAX)
	{
		if (shell->parser_status == PARSE_ERROR)
		{
			ft_free_everything(shell);
			return (-1);
		}
		ft_execute(shell, shell->cmd);
		g_status.file_is_folder = 0;
	}
	free(shell->buffer);
	shell->buffer = NULL;
	ft_free_everything(shell);
	return (0);
}

void	*ft_command_line(t_shell *shell)
{
	rl_catch_signals = 0;
	ft_handle_signals();
	while (1)
	{
		g_status.eof = 0;
		g_status.sigint = 0;
		if (shell->buffer)
			free(shell->buffer);
		shell->parser_status = 0;
		shell->buffer = readline(PROMPT);
		if (!shell->buffer)
			ft_ctrl_d(shell);
		if (ft_has_input(shell->buffer))
			if (ft_handle_command_line(shell) == -1)
				return (NULL);
	}
	return (0);
}
