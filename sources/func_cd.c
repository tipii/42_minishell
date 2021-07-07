/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:31:39 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/29 16:30:25 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_home(t_glob *g_glob, t_cmd *cmd)
{
	char	*home;
	char	*homevalue;

	home = ft_strdup("HOME");
	homevalue = search_and_replace(home, g_glob);
	g_glob->ret = chdir(homevalue);
	if (g_glob->ret == -1)
	{
		g_glob->ret = 1;
		error(cmd);
	}
	free(home);
	free(homevalue);
}

void	ft_replace_home(t_glob *g_glob, t_cmd *cmd)
{
	char	*home;
	char	*homevalue;

	home = ft_strdup("HOME");
	homevalue = search_and_replace(home, g_glob);
	free(home);
	home = ft_strjoin(homevalue, &cmd->argv[1][1]);
	free(homevalue);
	g_glob->ret = chdir(home);
	if (g_glob->ret == -1)
	{
		g_glob->ret = 1;
		error(cmd);
	}
	free(home);
}

void	run_cd(t_cmd *cmd, t_glob *g_glob)
{
	char	*buf;
	char	*pathname;

	buf = NULL;
	pathname = getcwd(buf, 0);
	if (cmd->argc == 1 || (cmd->argc == 2 && !ft_strcmp(cmd->argv[1], "~")))
		ft_cd_home(g_glob, cmd);
	else if (cmd->argv[1][0] == '~')
		ft_replace_home(g_glob, cmd);
	else
	{
		g_glob->ret = chdir(cmd->argv[1]);
		if (g_glob->ret == -1)
		{
			g_glob->ret = 1;
			error(cmd);
		}
	}
	free(pathname);
}
