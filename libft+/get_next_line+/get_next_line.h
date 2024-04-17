/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:54:37 by mgayout           #+#    #+#             */
/*   Updated: 2023/12/11 17:54:37 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

char	*get_next_line(int fd);
char	*ft_read(int fd, char *stash);
char	*ft_read2(int fd, char *stash, char *copy, int nbyte_read);
char	*ft_extract(char *tmp);
char	*ft_stash(char *str);
char	*ft_strjoingnl(char *s1, const char *s2);
size_t	ft_strlengnl(const char *str);
char	*ft_strchrgnl(const char *str, int c);
size_t	ft_strlcatgnl(char *dest, const char *src, size_t size);

#endif