/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:43:07 by tpalhol           #+#    #+#             */
/*   Updated: 2020/03/10 14:17:34 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast		*job1(void)
{
	t_ast	*cmd_node;
	t_ast	*job_node;
	t_ast	*result;

	if ((cmd_node = cmd()) == NULL)
		return (NULL);
	if (!term(CHAR_PIPE, NULL))
	{
		ast_delete_node(cmd_node);
		return (NULL);
	}
	if ((job_node = job()) == NULL)
	{
		ast_delete_node(cmd_node);
		return (NULL);
	}
	result = malloc(sizeof(*result));
	ast_set_data(result, NULL);
	ast_set_type(result, NODE_PIPE);
	ast_attach_branch(result, cmd_node, job_node);
	return (result);
}

t_ast		*job2(void)
{
	return (cmd());
}

t_ast		*job(void)
{
	t_tok	*save;
	t_ast	*node;

	save = g_curtok;
	g_curtok = save;
	if ((node = job1()) != NULL)
		return (node);
	g_curtok = save;
	if ((node = job2()) != NULL)
		return (node);
	return (NULL);
}
