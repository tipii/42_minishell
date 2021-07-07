/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:42:28 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 11:35:54 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast		*cmd0(void)
{
	t_ast	*simplecmd_node;
	t_ast	*result;
	char	*filename;

	if ((simplecmd_node = simple_cmd()) == NULL)
		return (NULL);
	if (!term(CHAR_DOBLEGREATER, NULL))
	{
		ast_delete_node(simplecmd_node);
		return (NULL);
	}
	if (!term(TOKEN, &filename))
	{
		ast_delete_node(simplecmd_node);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	ast_set_type(result, NODE_REDIRECT_AFTER);
	ast_set_data(result, filename);
	ast_attach_branch(result, NULL, simplecmd_node);
	return (result);
}

t_ast		*cmd1(void)
{
	t_ast	*simplecmd_node;
	t_ast	*result;
	char	*filename;

	if ((simplecmd_node = simple_cmd()) == NULL)
		return (NULL);
	if (!term(CHAR_LESSER, NULL))
	{
		ast_delete_node(simplecmd_node);
		return (NULL);
	}
	if (!term(TOKEN, &filename))
	{
		ast_delete_node(simplecmd_node);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	ast_set_type(result, NODE_REDIRECT_IN);
	ast_set_data(result, filename);
	ast_attach_branch(result, NULL, simplecmd_node);
	return (result);
}

t_ast		*cmd2(void)
{
	t_ast	*simplecmd_node;
	t_ast	*result;
	char	*filename;

	if ((simplecmd_node = simple_cmd()) == NULL)
		return (NULL);
	if (!term(CHAR_GREATER, NULL))
	{
		ast_delete_node(simplecmd_node);
		return (NULL);
	}
	if (!term(TOKEN, &filename))
	{
		ast_delete_node(simplecmd_node);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	ast_set_type(result, NODE_REDIRECT_OUT);
	ast_set_data(result, filename);
	ast_attach_branch(result, NULL, simplecmd_node);
	return (result);
}

t_ast		*cmd3(void)
{
	return (simple_cmd());
}

t_ast		*cmd(void)
{
	t_tok	*save;
	t_ast	*node;

	save = g_curtok;
	if ((node = cmd_red_out()) != NULL)
		return (node);
	g_curtok = save;
	if ((node = cmd_red_after()) != NULL)
		return (node);
	g_curtok = save;
	if ((node = cmd0()) != NULL)
		return (node);
	g_curtok = save;
	if ((node = cmd1()) != NULL)
		return (node);
	g_curtok = save;
	if ((node = cmd2()) != NULL)
		return (node);
	g_curtok = save;
	if ((node = cmd3()) != NULL)
		return (node);
	return (NULL);
}
