/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:30:07 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 15:47:31 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_lst(t_lst *lst)
{
	int		i;
	t_lst	*tmp;

	i = 0;
	tmp = lst;
	if (lst)
	{
		while (tmp)
		{
			lst = tmp;
			free(lst->name);
			free(lst->value);
			tmp = lst->next;
			free(lst);
			i++;
		}
	}
}

char	*str_back(char *str, char *replace, int i, char *s)
{
	int		tab[4];
	char	*new;

	tab[0] = 0;
	while (str[i + tab[0]] && s[tab[0]] && str[i + tab[0]] == s[tab[0]])
		tab[0]++;
	if (!s[tab[0]])
	{
		tab[1] = -1;
		tab[2] = -1;
		tab[3] = ft_strlen(str) - tab[0] + i + ft_strlen(replace);
		if (!(new = malloc(sizeof(char) * tab[3] + 1)))
			return (NULL);
		while (++tab[1] < i)
			new[tab[1]] = str[tab[1]];
		while (replace[++tab[2]])
			new[tab[1]++] = replace[tab[2]];
		while (str[i + tab[0] - 1])
			new[tab[1]++] = str[i + tab[0]++];
		new[++tab[1]] = '\0';
		free(str);
		str = new;
	}
	return (str);
}

char	*str_search_replace(char *str, char *search, char *replace, int i)
{
	while (str[++i])
		str = str_back(str, replace, i, search);
	return (str);
}

void	init_glob(t_glob *g_glob)
{
	g_glob->env = NULL;
	g_glob->exp = NULL;
	g_glob->ret = 0;
}
