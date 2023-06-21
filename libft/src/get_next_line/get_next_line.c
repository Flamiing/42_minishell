/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaaouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:26:39 by alaaouam          #+#    #+#             */
/*   Updated: 2023/03/15 10:52:38 by alaaouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

static char	*ft_read_to_stash(char *stash, char *buffer, ssize_t size)
{
	if (size == 0)
		return (stash);
	stash = ft_reallocstr(stash, size);
	if (!stash)
		return (NULL);
	ft_strcpy(&stash[ft_linelen(stash, '\0')], buffer, '\0');
	return (stash);
}

static char	*ft_read_buffer(int fd, char *stash)
{
	ssize_t	size;
	char	*buffer;

	size = 1;
	while (size > 0 && !ft_strchr(stash, '\n'))
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		size = read(fd, buffer, BUFFER_SIZE);
		if ((size == 0 && ft_linelen(stash, '\0') == 0) || size == -1)
		{
			free(buffer);
			if (ft_linelen(stash, '\0') == 0 || stash)
				free(stash);
			return (NULL);
		}
		buffer[size] = '\0';
		stash = ft_read_to_stash(stash, buffer, size);
		if (!stash)
			return (ft_freeptr(buffer));
		free(buffer);
	}
	return (stash);
}

static char	*ft_get_line(char *line, char *stash)
{
	size_t	has_newline;

	if (!stash)
		return (NULL);
	has_newline = ft_strchr(stash, '\n');
	if (has_newline)
	{
		line = (char *)malloc(ft_linelen(stash, '\n') + 2);
		if (!line)
			return (NULL);
	}
	else
	{
		line = (char *)malloc(ft_linelen(stash, '\0') + 1);
		if (!line)
			return (NULL);
	}
	if (has_newline)
		ft_strcpy(line, stash, '\n');
	else
		ft_strcpy(line, stash, '\0');
	return (line);
}

static void	*ft_clean_stash(char *stash, char *remove)
{
	size_t	index;
	char	*clean;
	int		size;

	if (ft_linelen(stash, '\0') == 0 && stash)
	{
		free(stash);
		return (NULL);
	}
	index = ft_linelen(remove, '\0');
	size = ft_linelen(stash, '\0') - index;
	clean = (char *)malloc(size + 1);
	if (!clean)
		return (NULL);
	ft_strcpy(clean, &stash[index], '\0');
	free(stash);
	return (clean);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	line = NULL;
	stash[fd] = ft_read_buffer(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	if (stash[fd] && (ft_strchr(stash[fd], '\n')
			|| ft_linelen(stash[fd], '\0') > 0))
	{
		line = ft_get_line(line, stash[fd]);
		if (!line)
			return (ft_freeptr(stash[fd]));
		stash[fd] = ft_clean_stash(stash[fd], line);
		if (!stash[fd])
			return (ft_freeptr(line));
	}
	return (line);
}
