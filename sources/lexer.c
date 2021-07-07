/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:17:09 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 11:47:30 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		lexer_general_state(t_lexer *l)
{
	if (l->char_type == CHAR_QUOTE || l->char_type == CHAR_DQUOTE ||
	l->char_type == CHAR_ESCAPESEQUENCE || l->char_type == CHAR_GENERAL)
	{
		lexer_char_quotes_esc_general(l);
	}
	else if (l->char_type == CHAR_WHITESPACE || l->char_type == CHAR_TAB)
	{
		if (l->j > 0)
		{
			l->token->data[l->j] = 0;
			l->token->next = malloc(sizeof(t_tok));
			l->token = l->token->next;
			tok_init(l->token, l->size - l->i);
			l->j = 0;
		}
	}
	else if (l->char_type == CHAR_SEMICOLON ||
		l->char_type == CHAR_GREATER || l->char_type == CHAR_LESSER ||
		l->char_type == CHAR_AMPERSAND || l->char_type == CHAR_PIPE)
		lexer_special_char(l);
}

void		lexer_quotes_state(t_lexer *l)
{
	if (l->state == STATE_IN_DQUOTE)
	{
		l->token->data[l->j++] = l->req[l->i];
		if (l->char_type == CHAR_DQUOTE)
			l->state = STATE_GENERAL;
	}
	else if (l->state == STATE_IN_QUOTE)
	{
		l->token->data[l->j++] = l->req[l->i];
		if (l->char_type == CHAR_QUOTE)
			l->state = STATE_GENERAL;
	}
}

void		lexer_char_null(t_lexer *l)
{
	if (l->j > 0)
	{
		l->token->data[l->j] = 0;
		l->j = 0;
	}
}

int			lexer_build(t_lexer *l)
{
	l->state = STATE_GENERAL;
	if (!l || l->size == 0)
		return (lexer_special_case(l));
	l->token = l->llisttok;
	tok_init(l->token, l->size);
	while (l->req[l->i] || l->i == 0)
	{
		l->char_type = get_char_type(l->req[l->i]);
		if (l->state == STATE_GENERAL)
			lexer_general_state(l);
		else if (l->state == STATE_IN_DQUOTE || l->state == STATE_IN_QUOTE)
			lexer_quotes_state(l);
		if (l->char_type == CHAR_NULL)
			lexer_char_null(l);
		l->i++;
	}
	l->token->data[l->j] = 0;
	l->token = l->llisttok;
	while (l->token)
		check_tokens(l);
	return (l->nbr_toks);
}
