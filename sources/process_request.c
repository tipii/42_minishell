/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_request.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:15:13 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 14:19:54 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			init_ms(t_ms *ms)
{
	ms->lexer = malloc(sizeof(t_lexer));
	ms->lexer->nbr_toks = 0;
	ms->lexer->llisttok = malloc(sizeof(t_tok));
	ms->lexer->req = NULL;
	ms->lexer->i = 0;
	ms->lexer->j = 0;
	ms->lexer->state = 0;
	ms->lexer->char_type = 0;
	ms->lexer->token = NULL;
	ms->lexer->size = 0;
	ms->cmd = malloc(sizeof(t_cmd));
	ms->cmd->argc = 0;
	ms->cmd->argv = NULL;
	ms->cmd->fd_pipe_read = 0;
	ms->cmd->fd_pipe_write = 0;
	ms->cmd->pipe_in = 0;
	ms->cmd->pipe_in = 0;
	ms->cmd->redirect_in = NULL;
	ms->cmd->redirect_out = NULL;
}

void			free_lexer(t_lexer *lexer)
{
	t_tok	*curseur;
	t_tok	*temp;

	curseur = lexer->llisttok;
	while (curseur)
	{
		if (curseur->data)
			free(curseur->data);
		temp = curseur->next;
		free(curseur);
		curseur = temp;
	}
	lexer->llisttok = NULL;
	if (lexer->token)
		free(lexer->token);
	lexer->token = NULL;
	if (lexer->req)
		free(lexer->req);
	lexer->req = NULL;
	free(lexer);
}

void			process_request(char *buf, t_glob *g_glob)
{
	t_ms	*ms;

	ms = malloc(sizeof(t_ms));
	init_ms(ms);
	ms->lexer->req = ft_strdup(buf);
	ms->lexer->size = ft_strlen(buf);
	lexer_build(ms->lexer);
	check_env(ms->lexer, g_glob);
	if (parse(ms->lexer, &ms->exectree) == 0)
	{
		free_lexer(ms->lexer);
		run_tree(ms, g_glob);
		ast_delete_node(ms->exectree);
	}
	free(ms->cmd);
	free(ms);
}
