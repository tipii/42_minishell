/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 11:35:42 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 11:38:41 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast		*cmd_red_out(void)
{
	t_ast	*cmd_node;
	t_ast	*result;
	char	*filename;

	if ((cmd_node = cmd1()) == NULL)
		return (NULL);
	if (!term(CHAR_GREATER, NULL))
	{
		ast_delete_node(cmd_node);
		return (NULL);
	}
	if (!term(TOKEN, &filename))
	{
		ast_set_data(cmd_node, filename);
		ast_delete_node(cmd_node);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	ast_set_type(result, NODE_REDIRECT_OUT);
	ast_set_data(result, filename);
	ast_attach_branch(result, NULL, cmd_node);
	return (result);
}

t_ast		*cmd_red_after(void)
{
	t_ast	*cmd_node;
	t_ast	*result;
	char	*filename;

	if ((cmd_node = cmd1()) == NULL)
		return (NULL);
	if (!term(CHAR_DOBLEGREATER, NULL))
	{
		ast_delete_node(cmd_node);
		return (NULL);
	}
	if (!term(TOKEN, &filename))
	{
		ast_delete_node(cmd_node);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	ast_set_type(result, NODE_REDIRECT_AFTER);
	ast_set_data(result, filename);
	ast_attach_branch(result, NULL, cmd_node);
	return (result);
}
