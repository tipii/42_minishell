/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:42:53 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/29 15:00:01 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok *g_curtok = NULL;

t_ast		*simple_cmd1(void)
{
	t_ast	*tokenlist_node;
	t_ast	*result;
	char	*pathname;

	if (!term(TOKEN, &pathname))
		return (NULL);
	tokenlist_node = token_list();
	result = malloc(sizeof(*result));
	ast_set_type(result, NODE_CMDPATH);
	ast_set_data(result, pathname);
	ast_attach_branch(result, NULL, tokenlist_node);
	return (result);
}

t_ast		*simple_cmd(void)
{
	return (simple_cmd1());
}

int			term(int toketype, char **bufferptr)
{
	if (g_curtok == NULL)
		return (0);
	if (g_curtok->type == toketype)
	{
		if (bufferptr != NULL)
			*bufferptr = ft_strdup(g_curtok->data);
		g_curtok = g_curtok->next;
		return (1);
	}
	g_curtok = g_curtok->next;
	return (0);
}

int			parse(t_lexer *lexer, t_ast **syntax_tree)
{
	if (lexer->nbr_toks == 0)
	{
		*syntax_tree = NULL;
		return (-1);
	}
	g_curtok = NULL;
	g_curtok = lexer->llisttok;
	*syntax_tree = command_line();
	if (g_curtok != NULL && g_curtok->type != 0)
	{
		ft_putstr_fd("Syntax error :", 2);
		ft_putstr_fd(g_curtok->data, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	return (0);
}
