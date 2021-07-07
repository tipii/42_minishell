/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:30:19 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 14:19:54 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*concat_path(char *str1, char *str2, char *str3)
{
	char	*result;
	char	*tmp;

	result = ft_strjoin(str1, str2);
	tmp = result;
	result = ft_strjoin(result, str3);
	free(tmp);
	return (result);
}

int			is_a_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len >= 1 && path[0] == '/')
		return (1);
	if (len >= 2 && path[0] == '.' && path[1] == '/')
		return (1);
	return (0);
}

char		*try_and_get_path(t_cmd *cmd, t_glob *g_glob)
{
	char	*path;
	char	**split_path;
	char	*try_path;
	int		i;

	if (is_a_path(cmd->argv[0]))
		return (cmd->argv[0]);
	i = 0;
	path = get_exp_value("PATH", g_glob);
	split_path = ft_split(path, ':');
	free(path);
	while (split_path && split_path[i])
	{
		try_path = concat_path(split_path[i], "/", cmd->argv[0]);
		if (open(try_path, O_RDONLY) > 0)
		{
			ft_freetab(split_path);
			return (try_path);
		}
		free(try_path);
		i++;
	}
	ft_freetab(split_path);
	return (cmd->argv[0]);
}
