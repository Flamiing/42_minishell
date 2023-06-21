/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:59:23 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 11:08:00 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	ft_count_valid_args(char **args)
{
	size_t	pos;
	size_t	count;

	pos = 0;
	count = 0;
	while (args[pos])
	{
		if (ft_is_valid_export(args, pos))
			count++;
		pos++;
	}
	return (count);
}

static char	**ft_get_old_variables(char **new_env, char **env)
{
	size_t	size;
	size_t	count;

	size = ft_arrlen(env);
	count = 0;
	while (count < size)
	{
		new_env[count] = ft_strdup(env[count]);
		if (!new_env[count])
		{
			ft_free_array(new_env);
			return (NULL);
		}
		count++;
	}
	return (new_env);
}

static char	**ft_add_new_variables(char **new_env, char **args)
{
	size_t	count;
	size_t	pos;
	size_t	size;

	count = 0;
	pos = 0;
	size = ft_arrlen(new_env);
	while (args[count])
	{
		if (ft_is_valid_export(args, count) == 1)
		{
			new_env[size + pos] = ft_strdup(args[count]);
			if (!new_env[size + pos])
			{
				ft_free_array(new_env);
				return (NULL);
			}
			pos++;
			g_status.exit_status = 0;
		}
		else if (ft_is_valid_export(args, count) == 0)
			ft_export_error(args[count]);
		count++;
	}
	return (new_env);
}

static void	*ft_export_process(t_shell *shell, char **args)
{
	size_t	size;
	size_t	args_count;
	char	**new_env;

	args_count = ft_count_valid_args(args);
	ft_remove_and_append(shell, args, args_count);
	size = ft_arrlen(shell->env);
	new_env = (char **)ft_calloc(size + args_count + 1, sizeof(char *));
	if (!new_env)
		return (ft_print_error(ERROR_MALLOC));
	if (ft_get_old_variables(new_env, shell->env) == NULL)
		return (ft_print_error(ERROR_MALLOC));
	if (ft_add_new_variables(new_env, args) == NULL)
		return (ft_print_error(ERROR_MALLOC));
	ft_free_array(shell->env);
	shell->env = new_env;
	return (new_env);
}

void	ft_export(t_shell *shell, char **args)
{
	size_t	size;

	size = ft_arrlen(args);
	if (size == 0)
		ft_export_without_args(shell);
	else
	{
		ft_export_process(shell, args);
		if (ft_write_env(shell, shell->env) == NULL)
			ft_print_error(ERROR_EXPORT_WRITE);
	}
}
