/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tree_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:14:34 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 14:19:54 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_job(t_ast *node, t_cmd *cmd, t_glob *g_glob)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
		execute_pipe(node, cmd, g_glob);
	else
		execute_command(node, cmd, g_glob);
}

void	execute_command_line(t_ast *node, t_cmd *cmd, t_glob *g_glob)
{
	cmd_reset_values(cmd);
	if (!node)
		return ;
	if (node->type == NODE_SEQ)
	{
		execute_job(node->left, cmd, g_glob);
		execute_command_line(node->right, cmd, g_glob);
	}
	else
		execute_job(node, cmd, g_glob);
}

void	run_tree(t_ms *ms, t_glob *g_glob)
{
	t_ast *root;
	t_cmd *cmd;

	root = ms->exectree;
	cmd = malloc(sizeof(t_cmd));
	execute_command_line(root, cmd, g_glob);
	free(cmd);
}
