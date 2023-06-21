/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:48:32 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 11:43:45 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	ft_add_arr(char **new_arr, char **add_arr)
{
	size_t	count;
	size_t	pos;

	count = 0;
	pos = 0;
	while (add_arr[pos])
	{
		new_arr[count] = add_arr[pos];
		pos++;
		count++;
	}
	return (count);
}

static char	**ft_add_to_array(char **new_arr, char **add_arr, char **old_arr,
	size_t reference)
{
	size_t	pos;
	size_t	count;
	size_t	size;

	size = ft_arrlen(add_arr) + ft_arrlen(old_arr);
	count = 0;
	pos = 0;
	while (count < size)
	{
		if (count == reference)
		{
			count += ft_add_arr(new_arr + count, add_arr);
			pos++;
			continue ;
		}
		new_arr[count] = old_arr[pos];
		pos++;
		count++;
	}
	return (new_arr);
}

static size_t	ft_replace_expanded_args(t_cmd *cmd, size_t reference)
{
	size_t	size;
	size_t	old_size;
	size_t	ref;
	char	**add_arr;
	char	**new_arr;

	old_size = ft_arrlen(cmd->args);
	add_arr = ft_split(cmd->args[reference], ' ');
	free(cmd->args[reference]);
	size = ft_arrlen(add_arr) + old_size;
	new_arr = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!new_arr)
	{
		ft_free_array(add_arr);
		ft_print_error(ERROR_MALLOC);
		return (0);
	}
	new_arr = ft_add_to_array(new_arr, add_arr, cmd->args, reference);
	ref = size - old_size;
	free(cmd->args);
	free(add_arr);
	cmd->args = new_arr;
	return (ref - 1);
}

t_cmd	*ft_expand_args(t_cmd *cmd)
{
	size_t	count;
	size_t	ref;

	if (cmd->args[1] == NULL)
		return (cmd);
	count = 0;
	ref = 0;
	while (cmd->raw_args[count])
	{
		if (ft_need_expansion(cmd->raw_args[count], cmd->args[count]))
		{
			ref += ft_replace_expanded_args(cmd, count + ref);
			if (ref == 0)
				return (NULL);
		}
		count++;
	}
	return (cmd);
}
