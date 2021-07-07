/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:16:53 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 14:19:54 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_dollar(char *str, t_glob *g_glob)
{
	if (str[0] == '$' && str[1] && str[1] == '?')
		str[1] = g_glob->ret;
}

void	echo_write_argvs(t_cmd *cmd, int pos, t_glob *g_glob)
{
	int		print_ret;

	(void)g_glob;
	print_ret = pos == 1 ? 1 : 0;
	while (cmd->argv[pos])
	{
		ft_putstr_fd(cmd->argv[pos], STDOUT_FILENO);
		if (pos != cmd->argc - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		pos++;
	}
	if (print_ret)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	run_echo(t_cmd *cmd, t_glob *g_glob)
{
	pid_t	pid;
	int		waitstatus;

	if ((pid = fork()) == 0)
	{
		handle_redirect(cmd);
		if (cmd->pipe_out)
			dup2(cmd->fd_pipe_write, STDOUT_FILENO);
		if (cmd->argc > 1)
		{
			if (ft_strcmp(cmd->argv[1], "-n") == 0)
				echo_write_argvs(cmd, 2, g_glob);
			else
				echo_write_argvs(cmd, 1, g_glob);
		}
		else
			ft_putstr_fd("\n", STDOUT_FILENO);
		exit(0);
	}
	else
	{
		waitpid(pid, &waitstatus, WUNTRACED);
		g_glob->ret = WEXITSTATUS(waitstatus);
	}
	return ;
}
