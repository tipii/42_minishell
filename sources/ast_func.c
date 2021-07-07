/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:18:09 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/18 15:03:03 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_attach_branch(t_ast *root, t_ast *left, t_ast *right)
{
	if (root == NULL)
		exit(0);
	root->left = left;
	root->right = right;
}

void	ast_set_type(t_ast *node, t_nodetype nodetype)
{
	if (node == NULL)
		exit(0);
	node->type = nodetype;
}

void	ast_set_data(t_ast *node, char *data)
{
	if (node == NULL)
		exit(0);
	if (data)
		node->data = data;
	else
		node->data = NULL;
}

void	ast_delete_node(t_ast *node)
{
	if (node == NULL)
		return ;
	if (node->data)
	{
		free(node->data);
		node->data = NULL;
	}
	ast_delete_node(node->left);
	ast_delete_node(node->right);
	free(node);
	node = NULL;
}
