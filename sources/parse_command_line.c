/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:42:38 by tpalhol           #+#    #+#             */
/*   Updated: 2020/03/10 15:18:53 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast		*command_line1(void)
{
	t_ast	*job_node;
	t_ast	*cmdline_node;
	t_ast	*result;

	if ((job_node = job()) == NULL)
		return (NULL);
	if (!term(CHAR_SEMICOLON, NULL))
	{
		ast_delete_node(job_node);
		return (NULL);
	}
	if ((cmdline_node = command_line()) == NULL)
	{
		ast_delete_node(job_node);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	ast_set_type(result, NODE_SEQ);
	ast_set_data(result, NULL);
	ast_attach_branch(result, job_node, cmdline_node);
	return (result);
}

t_ast		*command_line2(void)
{
	t_ast	*job_node;
	t_ast	*result;

	if ((job_node = job()) == NULL)
		return (NULL);
	if (!term(CHAR_SEMICOLON, NULL))
	{
		ast_delete_node(job_node);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	ast_set_type(result, NODE_SEQ);
	ast_set_data(result, NULL);
	ast_attach_branch(result, job_node, NULL);
	return (result);
}

t_ast		*command_line3(void)
{
	return (job());
}

t_ast		*command_line(void)
{
	t_tok	*save;
	t_ast	*node;

	save = g_curtok;
	g_curtok = save;
	if ((node = command_line1()) != NULL)
		return (node);
	g_curtok = save;
	if ((node = command_line2()) != NULL)
		return (node);
	g_curtok = save;
	if ((node = command_line3()) != NULL)
		return (node);
	return (NULL);
}
