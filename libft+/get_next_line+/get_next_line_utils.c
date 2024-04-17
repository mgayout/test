/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:54:14 by mgayout           #+#    #+#             */
/*   Updated: 2023/12/11 17:54:14 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoingnl(char *s1, const char *s2)
{
	char	*copy;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	copy = malloc(ft_strlengnl(s1) + ft_strlengnl(s2) + 1);
	if (!copy)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		copy[i + j] = s2[j];
		j++;
	}
	copy[i + j] = '\0';
	free(s1);
	return (copy);
}

size_t	ft_strlengnl(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchrgnl(const char *str, int c)
{
	char	cast_c;
	int		i;

	cast_c = (char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == cast_c)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == cast_c)
		return ((char *)&str[i]);
	return (0);
}

size_t	ft_strlcatgnl(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i] && i < size)
		i++;
	while (src[j] && (i + j + 1) < size)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < size)
		dest[i + j] = '\0';
	return (i + ft_strlengnl(src));
}
