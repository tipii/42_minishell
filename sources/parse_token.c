/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:42:45 by tpalhol           #+#    #+#             */
/*   Updated: 2020/03/10 15:19:13 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast		*token_list(void)
{
	t_tok	*save;
	t_ast	*node;

	save = g_curtok;
	g_curtok = save;
	if ((node = token_list1()) != NULL)
		return (node);
	g_curtok = save;
	if ((node = token_list2()) != NULL)
		return (node);
	return (NULL);
}

t_ast		*token_list1(void)
{
	t_ast	*tokenlist_node;
	t_ast	*result;
	char	*arg;

	if (!term(TOKEN, &arg))
		return (NULL);
	tokenlist_node = token_list();
	result = malloc(sizeof(*result));
	ast_set_type(result, NODE_ARGUMENT);
	ast_set_data(result, arg);
	ast_attach_branch(result, NULL, tokenlist_node);
	return (result);
}

t_ast		*token_list2(void)
{
	return (NULL);
}
