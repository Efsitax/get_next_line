/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kugurlu <kugurlu@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:42:59 by kugurlu           #+#    #+#             */
/*   Updated: 2026/02/11 22:23:27 by kugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*clear_str(char *str)
{
	free(str);
	return (NULL);
}

static char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;
	int		r_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (clear_str(stash));
	r_bytes = 1;
	while (!ft_strchr(stash, '\n') && r_bytes != 0)
	{
		r_bytes = read(fd, buffer, BUFFER_SIZE);
		if (r_bytes == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[r_bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (clear_str(buffer));
	}
	free(buffer);
	return (stash);
}

static char	*update_stash(char *stash, int len)
{
	char	*new_stash;

	if (!stash)
		return (NULL);
	if ((size_t)len >= ft_strlen(stash))
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_substr(stash, len, ft_strlen(stash) - len);
	free(stash);
	return (new_stash);
}

static char	*free_stash(char **stash)
{
	if (stash && *stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stash[4096];
	char		*line;
	int			i;

	if (fd < 0 || fd >= 4096 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_and_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	if (!*stash[fd])
		return (free_stash(&stash[fd]));
	i = 0;
	while (stash[fd][i] && stash[fd][i] != '\n')
		i++;
	i += (stash[fd][i] == '\n');
	line = ft_substr(stash[fd], 0, i);
	if (!line)
		return (free_stash(&stash[fd]));
	stash[fd] = update_stash(stash[fd], i);
	return (line);
}
