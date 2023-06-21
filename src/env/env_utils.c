/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:46:32 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 11:16:18 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_write_env(t_shell *shell, char **env)
{
	size_t	count;
	int		env_file;
	char	*var;

	env_file = open(shell->minishell_env_dir, O_WRONLY | O_CREAT | O_TRUNC,
			0666);
	if (env_file == -1)
		return (NULL);
	count = 0;
	while (env[count])
	{
		var = ft_strjoin(env[count], "\n");
		if (!var)
		{
			close(env_file);
			return (NULL);
		}
		write(env_file, var, ft_strlen(var));
		free(var);
		count++;
	}
	close(env_file);
	return (env);
}

static char	*ft_remove_newline(int file)
{
	char	*str;
	char	*new_str;

	str = get_next_line(file);
	new_str = ft_strtrim(str, "\n");
	free(str);
	return (new_str);
}

char	**ft_read_env(t_shell *shell)
{
	size_t	count;
	char	**new_env;
	int		env_file;
	size_t	size;

	size = ft_file_size(shell->minishell_env_dir);
	env_file = open(shell->minishell_env_dir, O_RDONLY);
	if (env_file == -1)
		return (NULL);
	new_env = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
	{
		close(env_file);
		return (NULL);
	}
	count = 0;
	while (count < size)
	{
		new_env[count] = ft_remove_newline(env_file);
		count++;
	}
	close(env_file);
	ft_free_array(shell->env);
	shell->env = new_env;
	return (shell->env);
}
