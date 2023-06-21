/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:57:03 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/21 17:05:49 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_status	g_status;

static void	ft_init_shell(t_shell *shell, char **env)
{
	g_status.cd_status = -1;
	shell->home_dir = getenv("HOME");
	shell->minishell_env_dir = ft_strjoin(getenv("PWD"), "/.minishell_env");
	shell->minishell_heredoc_dir = ft_strjoin(getenv("PWD"), "/.heredoc_");
	shell->buffer = NULL;
	shell->env = ft_copy_env(env);
	shell->parser_status = 0;
	shell->pipe_count = 0;
	shell->cmd_count = 0;
	shell->redir_count = 0;
	shell->heredoc_count = 0;
	shell->cmd = NULL;
	shell->tokens = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	g_status.exit_status = 0;
	ft_init_shell(&shell, env);
	ft_command_line(&shell);
	ft_destroy_shell(&shell);
	return (g_status.exit_status);
}
