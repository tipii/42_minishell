/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 15:06:31 by sadarnau          #+#    #+#             */
/*   Updated: 2020/06/30 12:05:08 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	*g_glob;

int		write_path(void)
{
	char	*buf;
	char	*pathname;
	int		i;
	int		j;

	buf = NULL;
	if (!(pathname = getcwd(buf, 0)))
		return (0);
	ft_putstr_fd(BLK, 2);
	ft_putstr_fd(CYNB, 2);
	ft_putstr_fd("minishell:", 2);
	ft_putstr_fd(RESET, 2);
	i = 0;
	while (pathname[i])
		i++;
	j = i - 2;
	while (pathname[j] != '/')
		j--;
	ft_putstr_fd(BRED, 2);
	ft_putstr_fd("~", 2);
	ft_putstr_fd(pathname, 2);
	ft_putstr_fd("$ ", 2);
	ft_putstr_fd(RESET, 2);
	free(pathname);
	return (1);
}

void	get_env_and_export(t_glob *g_glob, char *envp[])
{
	int		i;
	int		j;
	t_lst	*new;

	j = 0;
	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (!(envp[i][j] == '=' || envp[i][j] == '\0' || envp[i][j] == '\n'))
			j++;
		new = ft_env_new(envp[i], j);
		ft_add_back(&g_glob->env, new);
	}
	get_export(g_glob);
}

void	handle_sig(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\b", 2);
		write(1, "\n", 1);
		write_path();
	}
	else if (sig_num == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 2);
}

void	set_sig(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
}

int		main(int ac, char *av[], char *envp[])
{
	char	*command;

	(void)ac;
	(void)av;
	if (!(g_glob = malloc(sizeof(t_glob))))
		exit(0);
	init_glob(g_glob);
	get_env_and_export(g_glob, envp);
	set_sig();
	write(1, "\n", 2);
	while (write_path() && get_next_line(0, &command))
	{
		if (command[0] != '#' && command[0] != 0)
			process_request(command, g_glob);
		free(command);
		set_sig();
	}
	free(command);
	del_lst(g_glob->env);
	del_lst(g_glob->exp);
	free(g_glob);
}
