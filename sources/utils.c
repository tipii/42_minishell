/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:17:45 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/15 12:17:47 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_lst(t_lst **lst)
{
	t_lst *start;

	if (!lst)
		return ;
	start = *lst;
	while (start)
	{
		ft_putstr_fd(start->name, 1);
		ft_putstr_fd(" = ", 1);
		ft_putstr_fd(start->value, 1);
		ft_putstr_fd("\n", 1);
		start = start->next;
	}
}

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 || (s1[i] == 0 || s2[i] == 0))
		return (-1);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_add_back(t_lst **alst, t_lst *new)
{
	t_lst	*tmp;

	tmp = *alst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*alst = new;
}
