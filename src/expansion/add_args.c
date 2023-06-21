/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:56:33 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/08 17:27:24 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**ft_copy_args(char	**dest, char **src)
{
	size_t	count;
	size_t	pos;

	count = 0;
	pos = ft_arrlen(dest);
	while (src[count])
	{
		dest[pos] = ft_strdup(src[count]);
		if (!dest[pos])
		{
			ft_free_array(dest);
			return (ft_print_error(ERROR_MALLOC));
		}
		pos++;
		count++;
	}
	return (dest);
}

static char	**ft_transfer_args(char	**dest, char **src)
{
	size_t	count;

	count = 0;
	while (src[count])
	{
		dest[count] = src[count];
		count++;
	}
	return (dest);
}

char	**ft_add_args(t_cmd *cmd, char **add_args)
{
	size_t	size;
	char	**new_args;

	if (add_args[0] == NULL)
		return (cmd->args);
	new_args = NULL;
	size = ft_arrlen(cmd->args) + ft_arrlen(add_args);
	new_args = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!new_args)
	{
		ft_print_error(ERROR_MALLOC);
		return (cmd->args);
	}
	new_args = ft_transfer_args(new_args, cmd->args);
	new_args = ft_copy_args(new_args, add_args);
	if (!new_args)
		return (cmd->args);
	free(cmd->args);
	cmd->args = new_args;
	return (cmd->args);
}
