/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:43:49 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 11:16:01 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	ft_var_name_len(char *var)
{
	size_t	count;

	if (!var)
		return (0);
	count = 0;
	while (var[count] && var[count] != '=')
		count++;
	return (count);
}

static char	*ft_no_value(void)
{
	char	*no_value;

	no_value = (char *)ft_calloc(1, sizeof(char));
	if (!no_value)
		return (ft_print_error(ERROR_MALLOC));
	return (no_value);
}

static char	*ft_get_variable_value(char **env, char *var)
{
	size_t	count;
	size_t	len;
	size_t	var_len;
	size_t	size;
	char	*value;

	count = 0;
	len = ft_varlen(var) - 1;
	size = 0;
	while (env[count] && var[0] == '$')
	{
		var_len = ft_var_name_len(env[count]);
		if (ft_strncmp(env[count], var + 1, var_len) == 0 && len == var_len)
		{
			size = ft_strlen(env[count] + (len + 1));
			value = (char *)ft_calloc(size + 1, sizeof(char));
			if (!value)
				return (ft_print_error(ERROR_MALLOC));
			ft_strlcpy(value, env[count] + (len + 1), size + 1);
			return (value);
		}
		count++;
	}
	value = ft_no_value();
	return (value);
}

char	*ft_remove_interrogation(char *var, char *value)
{
	size_t	count;
	size_t	value_len;
	char	*new_var;

	count = 0;
	value_len = ft_strlen(value);
	new_var = (char *)ft_calloc((ft_strlen(var) - 2) + value_len + 1,
			sizeof(char));
	if (!new_var)
		return (var);
	while (var[count] && var[count] != '$' && var[count + 1] != '?')
		count++;
	ft_strlcpy(new_var, var, count + 1);
	ft_strlcpy(new_var + count, value, value_len + 1);
	ft_strlcpy(new_var + count + value_len, var + count + 2,
		ft_strlen(var + count + 2) + 1);
	free(value);
	free(var);
	return (new_var);
}

char	*ft_get_value(char **env, char *var, int mode)
{
	if (mode == 1)
		return (ft_itoa(g_status.exit_status));
	else
		return (ft_get_variable_value(env, var));
}
