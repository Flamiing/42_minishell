/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:57:14 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/10 12:54:08 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_parser_error(t_shell *shell, int status, int type)
{
	if (type == 0)
		ft_putstr_fd(PIPE_TO_NOTHING, 2);
	else if (type == TYPE_CMD || type == TYPE_ARG)
		ft_putstr_fd(NO_CLOSING_QUOTE, 2);
	else if (type == TYPE_HEREDOC)
		ft_putstr_fd(INPUT_NEAR, 2);
	else if (type == TYPE_HEREDOC + 1)
		ft_putstr_fd(HEREDOC_NEAR, 2);
	else if (type == TYPE_APPEND)
		ft_putstr_fd(APPEND_NEAR, 2);
	else if (type == TYPE_OTHERS)
		ft_putstr_fd(HEREDOC_NEAR, 2);
	else if (type == TYPE_INPUT)
		ft_putstr_fd(INPUT_NEAR, 2);
	else if (type == TYPE_OUTPUT)
		ft_putstr_fd(OUTPUT_NEAR, 2);
	else if (type == TYPE_PIPE)
		ft_putstr_fd(PIPE_NEAR, 2);
	else if (type == TYPE_NEWLINE)
		ft_putstr_fd(NEWLINE_NEAR, 2);
	ft_putchar_fd('\n', 2);
	shell->parser_status = status;
	return (status);
}

int	ft_parser(t_shell *shell, t_token **tokens)
{
	shell->parser_status = 0;
	shell->cmd_count = ft_count_cmds(tokens);
	shell->redir_count = ft_count_redirections(tokens);
	shell->heredoc_count = ft_count_heredoc(tokens);
	shell->cmd_list_size = shell->cmd_count + shell->redir_count
		+ shell->heredoc_count + shell->pipe_count;
	if (ft_has_syntax_error(shell, tokens))
	{
		g_status.exit_status = 2;
		return (SYNTAX);
	}
	if (ft_get_commands(shell, tokens) == NULL)
	{
		g_status.exit_status = 2;
		shell->parser_status = PARSE_ERROR;
		return (PARSE_ERROR);
	}
	return (0);
}
