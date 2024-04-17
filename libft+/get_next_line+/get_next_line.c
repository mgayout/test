/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:22:08 by mgayout           #+#    #+#             */
/*   Updated: 2023/12/11 12:22:08 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <fcntl.h>
//#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE];
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = ft_read(fd, stash);
	if (!tmp)
		return (NULL);
	line = ft_extract(tmp);
	if (!line)
	{
		free(tmp);
		return (NULL);
	}
	tmp = ft_stash(tmp);
	if (!tmp)
	{
		free(line);
		return (NULL);
	}
	stash[0] = '\0';
	ft_strlcatgnl(stash, tmp, ft_strlengnl(tmp) + 1);
	free(tmp);
	return (line);
}

char	*ft_read(int fd, char *stash)
{
	char	*copy;
	int		nbyte_read;

	nbyte_read = 1;
	copy = malloc(ft_strlengnl(stash) * sizeof(char) + 1);
	if (!copy)
		return (NULL);
	copy[0] = '\0';
	ft_strlcatgnl(copy, stash, ft_strlengnl(stash) + 1);
	if (!copy)
		return (NULL);
	copy = ft_read2(fd, stash, copy, nbyte_read);
	return (copy);
}

char	*ft_read2(int fd, char *stash, char *copy, int nbyte_read)
{
	while (!ft_strchrgnl(copy, '\n') && nbyte_read != 0)
	{
		nbyte_read = read(fd, stash, BUFFER_SIZE);
		if (nbyte_read == -1)
		{
			stash[0] = '\0';
			free(copy);
			return (NULL);
		}
		stash[nbyte_read] = '\0';
		copy = ft_strjoingnl(copy, stash);
		if (!copy || ft_strlengnl(copy) == 0)
		{
			free(copy);
			return (NULL);
		}
	}
	return (copy);
}

char	*ft_extract(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str)
		return (str);
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc((sizeof(char) * i) + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_stash(char *str)
{
	char	*stash;
	int		i;
	int		j;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	stash = malloc(((ft_strlengnl(str) - i) + 1) * sizeof(char));
	if (!stash)
		return (NULL);
	j = 0;
	while (str[i])
		stash[j++] = str[i++];
	stash[j] = '\0';
	free(str);
	return (stash);
}
/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (0);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("<> %s", line);
		free(line);
	}
	printf("\n", 1);
	close(fd);
	return (0);
}
*/