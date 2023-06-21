/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 23:02:12 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 11:09:56 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	ft_equal_pos(char *arg)
{
	size_t	count;

	count = 0;
	while (arg[count])
	{
		if (arg[count] == '=')
			return (count);
		count++;
	}
	return (count);
}

static void	*ft_add_to_remove_list(char **args, size_t id, char **rm_args,
	size_t *pos)
{
	if (ft_is_valid_export(args, id))
	{
		rm_args[*pos] = ft_substr(args[id], 0, ft_equal_pos(args[id]));
		if (!rm_args[*pos])
		{
			ft_free_array(rm_args);
			return (ft_print_error(ERROR_MALLOC));
		}
		*pos += 1;
	}
	return (rm_args);
}

static char	*ft_free_and_return_str(char *str, char *str2, char *new_arg)
{
	free(str);
	free(str2);
	return (new_arg);
}

static char	*ft_append_var(t_shell *shell, char **args, char *arg)
{
	size_t	count;
	size_t	len;
	char	*old_var;
	char	*new_arg;

	count = 0;
	arg = ft_remove_char(arg, '+');
	len = ft_strlen_x(arg, '=');
	old_var = ft_find_var(shell->env, arg, len);
	new_arg = ft_strjoin(old_var, arg + (len + 1));
	if (!new_arg)
		return (NULL);
	while (args[count])
	{
		if (ft_strncmp(args[count], arg, len) == 0
			&& len == ft_strlen_x(args[count], '+'))
			return (ft_free_and_return_str(arg, args[count], new_arg));
		count++;
	}
	free(arg);
	free(new_arg);
	return (arg);
}

char	**ft_remove_and_append(t_shell *shell, char **args, size_t valid_args)
{
	size_t	count;
	size_t	pos;
	char	**rm_args;

	count = 0;
	pos = 1;
	rm_args = (char **)ft_calloc(valid_args + 2, sizeof(char *));
	if (!rm_args)
		return (ft_print_error(ERROR_MALLOC));
	while (args[count])
	{
		rm_args[0] = ft_strdup("NOTHING");
		if (ft_has_plus_simbol(args[count]) && ft_is_valid_export(args, count))
		{
			args[count] = ft_append_var(shell, args, args[count]);
			if (!args[count])
				return (NULL);
		}
		if (ft_add_to_remove_list(args, count, rm_args, &pos) == NULL)
			return (NULL);
		count++;
	}
	ft_unset(shell, rm_args);
	ft_free_array(rm_args);
	return (args);
}
