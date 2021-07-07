/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:30:48 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 16:20:21 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			try_filepath(char *filepath)
{
	if (!is_a_path(filepath))
		return (1);
	if (open(filepath, O_DIRECTORY) != -1 || open(filepath, O_RDONLY) == -1)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putstr_fd(filepath, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (1);
}

char		*get_exp_value(char *search, t_glob *g_glob)
{
	t_lst	*tmp;
	char	*value;

	value = NULL;
	tmp = g_glob->exp;
	if (tmp)
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, search))
			{
				value = ft_strdup(tmp->value);
				break ;
			}
			else
				tmp = tmp->next;
		}
	}
	if (!value)
	{
		value = malloc(sizeof(char));
		value[0] = 0;
	}
	return (value);
}

void		handle_sigquit(int sig_num)
{
	char	*str;

	if (sig_num == SIGINT)
	{
		write(1, "\n", 1);
		g_glob->ret = 130;
	}
	else if (sig_num == SIGQUIT)
	{
		ft_putstr_fd("[1]	", 2);
		ft_putstr_fd(str = ft_itoa(g_glob->pid), 2);
		ft_putstr_fd("	quit", 2);
		ft_putstr_fd("\n", 2);
		kill(g_glob->pid, SIGTERM);
		g_glob->ret = 131;
		free(str);
	}
}

void		run_inside_execve(t_cmd *cmd, int stdoutfd)
{
	char	*path;

	if (cmd->pipe_in)
		dup2(cmd->fd_pipe_read, STDIN_FILENO);
	if (cmd->pipe_out)
		dup2(cmd->fd_pipe_write, STDOUT_FILENO);
	path = try_and_get_path(cmd, g_glob);
	if (try_filepath(path) &&
		(execve(path, cmd->argv, NULL)) == -1)
	{
		dup2(stdoutfd, STDOUT_FILENO);
		put_error_3("minishell: command not found: ", cmd->argv[0], "\n");
		exit(1);
	}
}

void		run_execve(t_cmd *cmd, t_glob *g_glob)
{
	int		stdoutfd;
	int		waitstatus;

	g_glob->ret = 0;
	if ((g_glob->pid = fork()) == -1)
		error(cmd);
	else if (g_glob->pid == 0)
	{
		stdoutfd = dup(STDOUT_FILENO);
		handle_redirect(cmd);
		run_inside_execve(cmd, stdoutfd);
		exit(0);
	}
	else
	{
		signal(SIGINT, handle_sigquit);
		signal(SIGQUIT, handle_sigquit);
		waitpid(g_glob->pid, &waitstatus, WUNTRACED);
		if (!(g_glob->ret == 131 || g_glob->ret == 130))
			g_glob->ret = WEXITSTATUS(waitstatus);
	}
}
