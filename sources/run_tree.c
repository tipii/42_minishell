/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:14:25 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 14:19:54 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_cmd *cmd)
{
	cmd->argc = 0;
	if (cmd->argv)
		ft_freetab(cmd->argv);
	if (cmd->redirect_in)
		free(cmd->redirect_in);
	if (cmd->redirect_out)
		free(cmd->redirect_out);
	if (cmd->redirect_after)
		free(cmd->redirect_after);
	cmd_reset_values(cmd);
}

void	execute_simple_command(t_ast *node, t_cmd *cmd, t_glob *g_glob)
{
	cmd_create_args(node, cmd);
	run_command(cmd, g_glob);
	free_command(cmd);
}

void	execute_command_red_after(t_ast *node, t_cmd *cmd, t_glob *g_glob)
{
	cmd_add_redirect_after(cmd, node->data);
	if (node->right->type == NODE_REDIRECT_IN)
	{
		cmd_add_redirect_in(cmd, node->right->data);
		execute_simple_command(node->right->right, cmd, g_glob);
	}
	else
		execute_simple_command(node->right, cmd, g_glob);
}

void	execute_command(t_ast *node, t_cmd *cmd, t_glob *g_glob)
{
	if (!node)
		return ;
	if (node->type == NODE_REDIRECT_IN)
	{
		cmd_add_redirect_in(cmd, node->data);
		execute_simple_command(node->right, cmd, g_glob);
	}
	else if (node->type == NODE_REDIRECT_OUT)
	{
		cmd_add_redirect_out(cmd, node->data);
		if (node->right->type == NODE_REDIRECT_IN)
		{
			cmd_add_redirect_in(cmd, node->right->data);
			execute_simple_command(node->right->right, cmd, g_glob);
		}
		else
			execute_simple_command(node->right, cmd, g_glob);
	}
	else if (node->type == NODE_REDIRECT_AFTER)
		execute_command_red_after(node, cmd, g_glob);
	else if (node->type == NODE_CMDPATH)
		execute_simple_command(node, cmd, g_glob);
}

void	execute_pipe(t_ast *node, t_cmd *cmd, t_glob *g_glob)
{
	t_ast	*job_node;
	int		fd[2];
	int		pipes[2];

	pipe(fd);
	pipes[0] = fd[0];
	pipes[1] = fd[1];
	cmd_manage_pipe(cmd, -2, pipes[1]);
	execute_command(node->left, cmd, g_glob);
	job_node = node->right;
	while (job_node && job_node->type == NODE_PIPE && close(pipes[1]) == 0)
	{
		pipe(fd);
		pipes[1] = fd[1];
		cmd_manage_pipe(cmd, pipes[0], pipes[1]);
		execute_command(job_node->left, cmd, g_glob);
		close(pipes[0]);
		pipes[0] = fd[0];
		job_node = job_node->right;
	}
	pipes[0] = fd[0];
	close(pipes[1]);
	cmd_manage_pipe(cmd, pipes[0], -2);
	execute_command(job_node, cmd, g_glob);
	close(pipes[0]);
}
