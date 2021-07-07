/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:55:42 by tpalhol           #+#    #+#             */
/*   Updated: 2020/02/11 14:29:16 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int		get_next_line(int fd, char **line);
size_t	ft_len_p(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strchr2(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);

#endif
