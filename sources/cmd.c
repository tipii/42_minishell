/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:21:37 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/29 16:43:10 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_manage_pipe(t_cmd *cmd, int pipe_in, int pipe_out)
{
	if (pipe_in == -2)
	{
		cmd->pipe_in = 0;
		cmd->fd_pipe_read = 0;
	}
	else
	{
		cmd->pipe_in = 1;
		cmd->fd_pipe_read = pipe_in;
	}
	if (pipe_out == -2)
	{
		cmd->pipe_out = 0;
		cmd->fd_pipe_write = 0;
	}
	else
	{
		cmd->pipe_out = 1;
		cmd->fd_pipe_write = pipe_out;
	}
}

void	cmd_handle_error(t_cmd *cmd)
{
	cmd->argc = 0;
}

int		cmd_get_nbr_args(t_ast *node)
{
	t_ast	*arg_node;
	int		i;

	i = 0;
	arg_node = node;
	while (arg_node && (arg_node->type == NODE_CMDPATH
	|| arg_node->type == NODE_ARGUMENT))
	{
		arg_node = arg_node->right;
		i++;
	}
	return (i);
}

void	cmd_create_args(t_ast *node, t_cmd *cmd)
{
	t_ast	*arg_node;
	int		i;

	if (!node || !(node->type == NODE_CMDPATH))
		return (cmd_handle_error(cmd));
	i = cmd_get_nbr_args(node);
	cmd->argv = malloc(sizeof(char*) * (i + 1));
	arg_node = node;
	i = 0;
	while (arg_node && (arg_node->type == NODE_CMDPATH
	|| arg_node->type == NODE_ARGUMENT))
	{
		cmd->argv[i] = malloc(sizeof(char) * (ft_strlen(arg_node->data) + 1));
		ft_strlcpy(cmd->argv[i], arg_node->data, ft_strlen(arg_node->data) + 1);
		arg_node = arg_node->right;
		i++;
	}
	cmd->argv[i] = 0;
	cmd->argc = i;
}

void	cmd_reset_values(t_cmd *cmd)
{
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->fd_pipe_read = 0;
	cmd->fd_pipe_write = 0;
	cmd->pipe_in = 0;
	cmd->pipe_out = 0;
	cmd->redirect_in = NULL;
	cmd->redirect_out = NULL;
	cmd->redirect_after = NULL;
}
