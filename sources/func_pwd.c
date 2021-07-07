/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:30:37 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 14:26:42 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_pwd(t_glob *g_glob)
{
	ft_putstr_fd("pwd: too many arguments\n", 2);
	g_glob->ret = 1;
}

void	pwd_write_path(char *pathname)
{
	write(STDOUT_FILENO, pathname, ft_strlen(pathname));
	write(STDOUT_FILENO, "\n", 1);
}

void	run_inside_pwd(t_cmd *cmd, char *pathname)
{
	handle_redirect(cmd);
	if (cmd->pipe_out)
		dup2(cmd->fd_pipe_write, STDOUT_FILENO);
	if (!pathname)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		exit(1);
	}
	else
		pwd_write_path(pathname);
	exit(0);
}

void	run_pwd(t_cmd *cmd, t_glob *g_glob)
{
	char	*buf;
	char	*pathname;
	pid_t	pid;
	int		waitstatus;

	if (cmd->argc > 1)
		return (error_pwd(g_glob));
	buf = NULL;
	pathname = getcwd(buf, 0);
	if ((pid = fork()) == 0)
		run_inside_pwd(cmd, pathname);
	else
	{
		waitpid(pid, &waitstatus, WUNTRACED);
		g_glob->ret = WEXITSTATUS(waitstatus);
	}
	free(pathname);
	return ;
}
