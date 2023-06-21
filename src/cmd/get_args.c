/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:17:43 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/19 11:13:10 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_parse_arg(char **env, char *arg)
{
	char	*temp;
	char	*arg_clean;

	if (ft_has_variable(arg))
	{
		temp = ft_get_var_values(env, ft_strdup(arg));
		arg_clean = ft_strtrim(temp, " \x09\x0A\x0B\x0C\x0D");
		free(temp);
		return (arg_clean);
	}
	else
		return (ft_strdup(arg));
}

static size_t	ft_count_args(t_token *tokens)
{
	t_token	*token;
	size_t	count;

	token = tokens;
	count = 0;
	while (token != NULL && token->type == TYPE_ARG)
	{
		count++;
		token = token->next;
	}
	return (count);
}

char	**ft_get_args(char *path, char **env, t_token *tokens)
{
	t_token	*token;
	char	**args;
	size_t	size;
	size_t	count;

	token = tokens->next;
	size = ft_count_args(token);
	args = (char **)ft_calloc(size + 2, sizeof(char *));
	if (!args)
		return (ft_print_error(ERROR_MALLOC));
	count = 0;
	args[count] = ft_strdup(path);
	count++;
	while (token != NULL && token->type == TYPE_ARG)
	{
		args[count] = ft_parse_arg(env, token->data);
		count++;
		token = token->next;
	}
	return (args);
}

char	**ft_get_raw_args(char *path, t_token *tokens)
{
	t_token	*token;
	char	**raw_args;
	size_t	size;
	size_t	count;

	token = tokens->next;
	size = ft_count_args(token);
	raw_args = (char **)ft_calloc(size + 2, sizeof(char *));
	if (!raw_args)
		return (ft_print_error(ERROR_MALLOC));
	count = 0;
	raw_args[count] = ft_strdup(path);
	count++;
	while (token != NULL && token->type == TYPE_ARG)
	{
		raw_args[count] = ft_strdup(token->data);
		count++;
		token = token->next;
	}
	return (raw_args);
}
