/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 12:05:54 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/29 14:53:09 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_env_while(t_ce *ce, t_lexer *lexer)
{
	while (ce->tmp_split[ce->i])
	{
		if (ce->i == 0)
		{
			ce->new = tok_forge(ce->tmp_split[ce->i], ce->cursor->next);
			if (ce->previous)
				ce->previous->next = ce->new;
			else
				lexer->llisttok = ce->new;
			ce->new->next = ce->cursor->next;
			ce->cursor = ce->new;
		}
		else
		{
			ce->new = tok_forge(ce->tmp_split[ce->i], ce->cursor->next);
			ce->cursor->next = ce->new;
		}
		ce->i++;
	}
}

void	check_env_else(t_lexer *lexer, t_ce *ce)
{
	if (ce->previous)
		ce->previous->next = ce->cursor->next;
	else
		lexer->llisttok = ce->cursor->next;
	ce->cursor = ce->cursor->next;
}

void	check_env_init_ce(t_lexer *lexer, t_ce *ce)
{
	ce->i = 0;
	ce->cursor = lexer->llisttok;
	ce->previous = NULL;
	ce->new = NULL;
	ce->save = NULL;
}

void	check_env_if_isenv(t_lexer *lexer, t_ce *ce)
{
	if (ft_tablen(ce->tmp_split = ft_split(ce->tmp, ' ')) > 1)
		check_env_while(ce, lexer);
	else
	{
		free(ce->cursor->data);
		ce->cursor->data = ft_strdup(ce->tmp);
	}
	ft_freetab(ce->tmp_split);
}

void	check_env_isempty(t_lexer *lexer, t_ce *ce)
{
	ce->save = ce->cursor;
	if (ce->cursor->next)
	{
		if (ce->previous)
			ce->previous->next = ce->cursor->next;
		else
			lexer->llisttok = ce->cursor->next;
		ce->cursor = ce->cursor->next;
	}
	else
	{
		if (ce->previous)
			ce->previous->next = NULL;
		else
			lexer->llisttok = NULL;
		ce->cursor = NULL;
	}
	free(ce->save->data);
	free(ce->save);
}
