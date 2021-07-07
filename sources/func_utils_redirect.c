/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 13:19:51 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 13:20:34 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		redirect_error_msg(char *msg)
{
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void		handle_redirect_out_after(t_cmd *cmd)
{
	int	fd;

	if (cmd->redirect_out)
	{
		fd = open(cmd->redirect_out, O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
		{
			redirect_error_msg(cmd->redirect_out);
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
	}
	else if (cmd->redirect_after)
	{
		fd = open(cmd->redirect_after, O_WRONLY | O_CREAT | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
		{
			redirect_error_msg(cmd->redirect_after);
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
	}
}

void		handle_redirect(t_cmd *cmd)
{
	int	fd;

	if (cmd->redirect_in)
	{
		fd = open(cmd->redirect_in, O_RDONLY);
		if (fd == -1)
		{
			redirect_error_msg(cmd->redirect_in);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
	}
	handle_redirect_out_after(cmd);
}
