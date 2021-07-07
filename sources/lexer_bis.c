/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:17:16 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/15 12:17:18 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				get_char_type(char c)
{
	if (c == '\'')
		return (CHAR_QUOTE);
	else if (c == '\"')
		return (CHAR_DQUOTE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == '&')
		return (CHAR_AMPERSAND);
	else if (c == ' ')
		return (CHAR_WHITESPACE);
	else if (c == ';')
		return (CHAR_SEMICOLON);
	else if (c == '\\')
		return (CHAR_ESCAPESEQUENCE);
	else if (c == '\t')
		return (CHAR_TAB);
	else if (c == '\n')
		return (CHAR_NEWLINE);
	else if (c == '>')
		return (CHAR_GREATER);
	else if (c == '<')
		return (CHAR_LESSER);
	else if (c == 0)
		return (CHAR_NULL);
	return (CHAR_GENERAL);
}

void			lexer_special_char(t_lexer *l)
{
	if (l->j > 0)
	{
		l->token->data[l->j] = 0;
		l->token->next = malloc(sizeof(t_tok));
		l->token = l->token->next;
		tok_init(l->token, l->size - l->i);
		l->j = 0;
	}
	if (l->char_type == CHAR_GREATER &&
		get_char_type(l->req[l->i + 1]) == CHAR_GREATER)
	{
		l->char_type = CHAR_DOBLEGREATER;
		l->i++;
	}
	l->token->data[0] = l->char_type;
	l->token->data[1] = 0;
	l->token->type = l->char_type;
	l->token->next = malloc(sizeof(t_tok));
	l->token = l->token->next;
	tok_init(l->token, l->size - l->i);
}

void			lexer_char_quotes_esc_general(t_lexer *l)
{
	if (l->char_type == CHAR_QUOTE)
	{
		l->state = STATE_IN_QUOTE;
		l->token->data[l->j++] = CHAR_QUOTE;
		l->token->type = TOKEN;
	}
	else if (l->char_type == CHAR_DQUOTE)
	{
		l->state = STATE_IN_DQUOTE;
		l->token->data[l->j++] = CHAR_DQUOTE;
		l->token->type = TOKEN;
	}
	else if (l->char_type == CHAR_ESCAPESEQUENCE)
	{
		l->token->data[l->j++] = l->req[++l->i];
		l->token->type = TOKEN;
	}
	else if (l->char_type == CHAR_GENERAL)
	{
		l->token->data[l->j++] = l->req[l->i];
		l->token->type = TOKEN;
	}
}
