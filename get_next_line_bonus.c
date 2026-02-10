/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kugurlu <kugurlu@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:42:59 by kugurlu           #+#    #+#             */
/*   Updated: 2026/02/10 22:00:21 by kugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;
	int		r_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
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
	}
	free(buffer);
	return (stash);
}

static char	*update_stash(char *stash, int len)
{
	char	*new_stash;

	new_stash = ft_substr(stash, len, ft_strlen(stash));
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[4096];
	char		*line;
	int			i;
	int			len;

	if (fd < 0 || fd >= 4096 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 8388608)
		return (NULL);
	stash[fd] = read_and_stash(fd, stash[fd]);
	if (!stash[fd] || *stash[fd] == '\0')
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	i = 0;
	while (stash[fd][i] && stash[fd][i] != '\n')
		i++;
	len = i;
	if (stash[fd][i] == '\n')
		len++;
	line = ft_substr(stash[fd], 0, len);
	stash[fd] = update_stash(stash[fd], len);
	return (line);
}
