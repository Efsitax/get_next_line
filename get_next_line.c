/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kugurlu <kugurlu@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:56:44 by kugurlu           #+#    #+#             */
/*   Updated: 2026/02/10 21:59:59 by kugurlu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(stash, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
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
	static char	*stash;
	char		*line;
	int			i;
	int			len;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 8388608)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (!stash || *stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	len = i;
	if (stash[i] == '\n')
		len++;
	line = ft_substr(stash, 0, len);
	stash = update_stash(stash, len);
	return (line);
}
