/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:17:45 by alaaouam          #+#    #+#             */
/*   Updated: 2023/05/25 14:50:37 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_free_strings(char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

static char	*ft_path_not_found(char *cmd)
{
	char	*copy;

	copy = (char *)ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	if (!copy)
		return (ft_print_error(ERROR_MALLOC));
	ft_strlcpy(copy, cmd, ft_strlen(cmd) + 1);
	return (copy);
}

static char	*ft_getcmd_path(char **path_arr, char *cmd)
{
	size_t	count;
	char	*path;
	char	*cmd_path;

	count = 0;
	cmd_path = NULL;
	if (ft_begin_with_space(cmd))
		return (ft_get_with_space(cmd_path, cmd));
	while (path_arr[count])
	{
		path = ft_strjoin(path_arr[count], "/");
		cmd_path = ft_strjoin(path, cmd);
		if (access(cmd_path, F_OK & X_OK) == 0)
		{
			free(path);
			return (cmd_path);
		}
		ft_free_strings(path, cmd_path);
		count++;
	}
	return (ft_path_not_found(cmd));
}

char	*ft_get_path(char **env, char *cmd)
{
	size_t	count;
	char	**path_arr;
	char	*cmd_path;

	if (!env || !cmd)
		return (NULL);
	if (cmd[0] == '\0')
		return (ft_path_not_found(cmd));
	count = 0;
	while (env[count] && ft_strnstr(env[count], "PATH=", 5) == 0)
		count++;
	if (count == ft_arrlen(env))
		return (ft_path_not_found(cmd));
	path_arr = ft_split(env[count] + 5, 58);
	if (!path_arr)
		return (NULL);
	cmd_path = ft_getcmd_path(path_arr, cmd);
	ft_free_array(path_arr);
	return (cmd_path);
}
