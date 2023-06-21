/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:58:19 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 11:13:55 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_has_quotes_but_is_var(char *cmd, size_t count)
{
	size_t	pos;
	int		inside_quote;

	pos = 0;
	inside_quote = 0;
	while (cmd[pos])
	{
		if (cmd[pos] == SINGLE_QUOTE)
			inside_quote++;
		if (inside_quote == 2)
			inside_quote = 0;
		if (pos == count && inside_quote == 0)
			return (1);
		else if (pos == count && inside_quote == 1)
			return (0);
		pos++;
	}
	return (1);
}

int	ft_has_variable(char *cmd)
{
	size_t	count;

	if (!cmd)
		return (0);
	count = 0;
	while (cmd[count])
	{
		if (cmd[count] == '$' && ft_has_quotes_but_is_var(cmd, count)
			&& (ft_isalnum(cmd[count + 1]) || cmd[count + 1] == DOUBLE_QUOTE
				|| cmd[count + 1] == SINGLE_QUOTE
				|| cmd[count + 1] == ' ' || cmd[count + 1] == '_'
				|| (cmd[count + 1] > 8 && cmd[count + 1] <= 13)
				|| cmd[count + 1] == '\\' || cmd[count + 1] == '?'))
			return (1);
		count++;
	}
	return (0);
}

char	*ft_parse_cmd(t_cmd *cmd, char **env, char *command)
{
	char	*temp;
	char	*cmd_clean;

	cmd->raw_with_var = NULL;
	if (ft_has_variable(command))
	{
		cmd->raw_with_var = ft_strdup(command);
		if (!cmd->raw_with_var)
			return (NULL);
		temp = ft_get_var_values(env, ft_strdup(command));
		cmd_clean = ft_strtrim(temp, " \x09\x0A\x0B\x0C\x0D");
		free(temp);
		return (cmd_clean);
	}
	else
		return (ft_strdup(command));
}

char	*ft_to_lower(char *str)
{
	size_t	count;
	size_t	size;
	char	*lower_case;

	if (!str)
		return (NULL);
	count = 0;
	size = ft_strlen(str);
	lower_case = (char *)ft_calloc(size + 1, sizeof(char));
	if (!lower_case)
		return (NULL);
	while (str[count])
	{
		lower_case[count] = ft_tolower(str[count]);
		count++;
	}
	return (lower_case);
}
