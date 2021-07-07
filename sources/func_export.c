/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:30:43 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 14:19:54 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*ft_exp_new(char *str, int eq_p)
{
	t_lst *tmp;

	if (!(tmp = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	if (tmp)
	{
		tmp->name = ft_substr(str, 7, eq_p - 7);
		if (str[eq_p] != '\0')
			tmp->value = ft_substr(str, eq_p + 2, ft_strlen(str) - eq_p - 3);
		else
			tmp->value = ft_strdup("");
		tmp->next = NULL;
	}
	return (tmp);
}

void	get_export(t_glob *g_glob)
{
	int		fd;
	char	*line;
	int		i;
	t_lst	*new;
	int		ret;

	if ((fd = open("objs/export.txt", O_RDONLY)) == -1)
		exit(1);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		i = 7;
		while (!(line[i] == '=' || line[i] == '\0'))
			i++;
		new = ft_exp_new(line, i);
		ft_add_back(&g_glob->exp, new);
		free(line);
	}
	free(line);
	close(fd);
}

void	run_export(t_cmd *cmd, t_glob *g_glob)
{
	int		i;
	t_lst	*new;
	t_lst	*new2;

	i = 0;
	if (cmd->argc == 1)
		ft_print_lst(&g_glob->exp);
	else if (cmd->argc == 2)
	{
		while (!(cmd->argv[1][i] == '=' || cmd->argv[1][i] == '\0'))
			i++;
		new = ft_env_new(cmd->argv[1], i);
		new2 = ft_env_new(cmd->argv[1], i);
		if (!check_and_replace(new, new2, g_glob))
		{
			ft_add_back(&g_glob->exp, new);
			ft_add_back(&g_glob->env, new2);
		}
	}
	else
		ft_putstr_fd("minishell: bad assignment\n", 2);
	g_glob->ret = 0;
}

int		check_and_replace_env(t_lst *new, t_glob *g_glob)
{
	t_lst	*tmp;

	tmp = g_glob->env;
	if (tmp)
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, new->name))
			{
				free(tmp->value);
				tmp->value = ft_strdup(new->value);
				free(new);
				return (1);
			}
			else
				tmp = tmp->next;
		}
	}
	return (0);
}

int		check_and_replace(t_lst *new, t_lst *new2, t_glob *g_glob)
{
	t_lst	*tmp;

	tmp = g_glob->exp;
	if (tmp)
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, new->name))
			{
				free(tmp->value);
				tmp->value = ft_strdup(new->value);
				free(new);
				check_and_replace_env(new2, g_glob);
				return (1);
			}
			else
				tmp = tmp->next;
		}
	}
	return (0);
}
