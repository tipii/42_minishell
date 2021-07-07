/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:30:29 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 17:01:39 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_unset_env(t_cmd *cmd, t_glob *g_glob)
{
	t_lst	*tmp;
	t_lst	*before;
	int		i;

	i = 0;
	while (cmd->argv[++i])
	{
		tmp = g_glob->env;
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, cmd->argv[i]))
			{
				before->next = tmp->next;
				free(tmp->name);
				free(tmp->value);
				free(tmp);
				tmp = before->next;
				return ;
			}
			before = tmp;
			tmp = tmp->next;
		}
	}
}

void	unset_not_enough_args(t_glob *g_glob)
{
	g_glob->ret = 1;
	ft_putstr_fd("unset: not enough arguments\n", 2);
}

void	unset_if(t_lst *tmp, t_lst *before, t_cmd *cmd, t_glob *g_glob)
{
	before->next = tmp->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	tmp = before->next;
	run_unset_env(cmd, g_glob);
}

void	run_unset(t_cmd *cmd, t_glob *g_glob)
{
	t_lst	*tmp;
	t_lst	*before;
	int		i;

	g_glob->ret = 0;
	i = 0;
	if (cmd->argc == 1)
		unset_not_enough_args(g_glob);
	else
		while (cmd->argv[++i])
		{
			tmp = g_glob->exp;
			while (tmp)
			{
				if (!ft_strcmp(tmp->name, cmd->argv[i]))
				{
					unset_if(tmp, before, cmd, g_glob);
					break ;
				}
				before = tmp;
				tmp = tmp->next;
			}
		}
}
