/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:17:23 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/29 13:22:12 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		tok_init(t_tok *tok, int size)
{
	if (!(tok->data = malloc(sizeof(char) * (size + 1))))
		exit(0);
	tok->data[0] = 0;
	tok->type = CHAR_NULL;
	tok->next = NULL;
}

void		*if_no_data(t_tok *tok)
{
	free(tok->data);
	return (NULL);
}

char		*format_data(t_tok *tok)
{
	char	*src;
	char	*dest;
	size_t	i;
	int		lastquote;
	int		j;

	i = -1;
	j = 0;
	lastquote = 0;
	src = tok->data;
	if (!tok->data)
		return (if_no_data(tok));
	dest = malloc(sizeof(char) * (ft_strlen(src) + 1));
	while (++i < ft_strlen(src))
	{
		if ((src[i] == '\'' || src[i] == '\"') && lastquote == 0)
			lastquote = src[i];
		else if (src[i] == lastquote)
			lastquote = 0;
		else
			dest[j++] = src[i];
	}
	dest[j] = 0;
	free(tok->data);
	return (dest);
}

void		check_tokens(t_lexer *l)
{
	if (l->token->type == TOKEN)
		l->token->data = format_data(l->token);
	l->token = l->token->next;
	l->nbr_toks++;
}

int			lexer_special_case(t_lexer *l)
{
	if (!l)
		return (-1);
	else
	{
		l->nbr_toks = 0;
		return (0);
	}
}
