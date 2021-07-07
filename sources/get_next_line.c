/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:04:24 by tpalhol           #+#    #+#             */
/*   Updated: 2020/03/03 14:54:01 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*init_or_error(char *tmp)
{
	if (!tmp)
	{
		if (!(tmp = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (NULL);
		tmp[0] = '\0';
	}
	return (tmp);
}

char		*fill_tmp(char *tmp, int fd, char *buf)
{
	int				ret;
	char			*oldtmp;

	while (ft_strchr2(tmp, '\n') == -1 &&
		(ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = 0;
		oldtmp = tmp;
		tmp = ft_strjoin(tmp, buf);
		free(oldtmp);
	}
	return (tmp);
}

char		*ft_substrandfree(char *tmp, int i, char **line, int ret)
{
	char	*oldtmp;

	if (i == 0)
		*line = ft_strdup("");
	else
		*line = ft_substr(tmp, 0, i);
	if (ret)
	{
		oldtmp = tmp;
		tmp = ft_substr(tmp, i + 1, ft_len_p(tmp));
		free(oldtmp);
	}
	else
	{
		oldtmp = tmp;
		tmp = NULL;
		free(oldtmp);
	}
	return (tmp);
}

int			get_next_line(int fd, char **line)
{
	static char		*tmp[1024];
	char			buf[BUFFER_SIZE + 1];
	int				i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE == 0 || !(line) || read(fd, buf, 0) < 0)
		return (-1);
	if (!(tmp[fd] = init_or_error(tmp[fd])))
		return (-1);
	tmp[fd] = fill_tmp(tmp[fd], fd, buf);
	while (tmp[fd][i] && tmp[fd][i] != '\n')
		i++;
	if (ft_strchr2(tmp[fd], '\n') != -1)
	{
		tmp[fd] = ft_substrandfree(tmp[fd], i, line, 1);
		return (1);
	}
	else
	{
		tmp[fd] = ft_substrandfree(tmp[fd], i, line, 0);
		return (0);
	}
}
