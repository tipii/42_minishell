/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:30:54 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/29 14:54:54 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*ft_env_new(char *str, int equal_pos)
{
	t_lst *tmp;

	if (!(tmp = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	if (tmp)
	{
		tmp->name = ft_substr(str, 0, equal_pos);
		tmp->value = ft_substr(str, equal_pos + 1, ft_strlen(str) - equal_pos);
		tmp->next = NULL;
	}
	return (tmp);
}

char	*search_and_replace(char *name, t_glob *g_glob)
{
	t_lst	*tmp;

	tmp = g_glob->env;
	if (tmp)
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, name))
				return (ft_strdup(tmp->value));
			else
				tmp = tmp->next;
		}
	return (ft_strdup(""));
}

t_tok	*tok_forge(char *data, t_tok *next)
{
	t_tok	*tok;

	tok = malloc(sizeof(t_tok));
	tok->data = ft_strdup(data);
	tok->type = TOKEN;
	tok->next = next;
	return (tok);
}

void	get_next_tok(t_ce *ce)
{
	ce->previous = ce->cursor;
	ce->cursor = ce->cursor->next;
}

void	check_env(t_lexer *lexer, t_glob *g_glob)
{
	t_ce	*ce;

	ce = malloc(sizeof(t_ce));
	check_env_init_ce(lexer, ce);
	while (ce->cursor)
	{
		if (ce->cursor->data && (ce->cursor->data[0] == '$'
			&& ce->cursor->data[1] && ce->cursor->data[1] != ' '
			&& ce->cursor->data[1] != '?'))
		{
			ce->tmp = search_and_replace(ce->cursor->data + 1, g_glob);
			if (ce->tmp[0] != 0)
			{
				check_env_if_isenv(lexer, ce);
				ce->previous = ce->cursor;
				ce->cursor = ce->cursor->next;
			}
			else
				check_env_isempty(lexer, ce);
			free(ce->tmp);
		}
		else
			get_next_tok(ce);
	}
	free(ce);
}
