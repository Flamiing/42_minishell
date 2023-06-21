/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:59:33 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 11:09:37 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_wrong_unset_argument(char *argument)
{
	ft_putstr_fd("minishell: unset: ", 2);
	ft_putchar_fd(argument[0], 2);
	ft_putchar_fd(argument[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("unset: usage: unset [name]\n", 2);
	g_status.exit_status = 1;
}

static char	**ft_remove_variable(char **env, size_t id)
{
	size_t	count;
	size_t	pos;
	size_t	size;
	char	**new_env;

	size = ft_arrlen(env) - 1;
	new_env = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	count = 0;
	pos = 0;
	while (env[count])
	{
		if (count != id)
		{
			new_env[pos] = env[count];
			pos++;
		}
		count++;
	}
	free(env[id]);
	free(env);
	return (new_env);
}

static char	**ft_unset_variables(char *arg, char **env, size_t len)
{
	size_t	count;
	char	**new_env;
	char	*var;

	count = 0;
	new_env = ft_copy_env(env);
	while (env[count])
	{
		var = ft_substr(env[count], 0, len);
		if (!var)
		{
			ft_free_array(new_env);
			return (NULL);
		}
		if (ft_strncmp(arg, var, len) == 0 && len == ft_strlen(var))
		{
			new_env = ft_remove_variable(new_env, count);
			if (!new_env)
				return (ft_print_error(ERROR_UNSET));
		}
		free(var);
		count++;
	}
	ft_free_array(env);
	return (new_env);
}

void	ft_unset(t_shell *shell, char **args)
{
	size_t	args_count;
	size_t	count;
	size_t	len;
	char	**new_env;

	args_count = ft_arrlen(args);
	if (args_count > 1 && args[1][0] == '-' && args[1][1])
		ft_wrong_unset_argument(args[1]);
	else
	{
		count = 1;
		while (args[count])
		{
			len = ft_strlen(args[count]);
			new_env = ft_unset_variables(args[count], shell->env, len);
			if (!new_env)
			{
				ft_print_error(ERROR_UNSET);
				return ;
			}
			shell->env = new_env;
			count++;
		}
	}
	g_status.exit_status = 0;
}
