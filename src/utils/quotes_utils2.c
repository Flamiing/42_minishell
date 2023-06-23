/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:55:43 by alaaouam          #+#    #+#             */
/*   Updated: 2023/06/23 12:12:57 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_get_opposite(int type)
{
	int	opposite;

	if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
	{
		if (type == SINGLE_QUOTE)
			opposite = DOUBLE_QUOTE;
		else
			opposite = SINGLE_QUOTE;
		return (opposite);
	}
	return (0);
}

void	ft_reset_quote_counts(size_t *quote_count, int *opposite)
{
	if (*quote_count == 2)
			*quote_count = 0;
	if (*opposite == 2)
		*opposite = 0;
}
