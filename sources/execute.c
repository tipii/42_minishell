/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:31:34 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/29 13:14:47 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_exit(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	else if (cmd->argc == 2)
	{
		while (cmd->argv[1][++i])
			if (ft_isalpha(cmd->argv[1][i]))
				exit(-1);
		exit(ft_atoi(cmd->argv[1]));
	}
	exit(0);
}

void	check_arg_env(t_cmd *cmd, t_glob *g_glob)
{
	if (cmd->argc > 1)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_glob->ret = 127;
	}
	else
		ft_print_lst(&g_glob->env);
}

void	replace_dollar(t_cmd *cmd, t_glob *g_glob)
{
	int		i;
	char	*str;

	i = -1;
	while (cmd->argv[++i])
	{
		cmd->argv[i] = str_search_replace(cmd->argv[i], "$?",
			str = ft_itoa(g_glob->ret), -1);
		free(str);
	}
}

void	run_command(t_cmd *cmd, t_glob *g_glob)
{
	if (cmd->argc < 0)
		return ;
	if (ft_strcmp(cmd->argv[0], "$?") == 0 && get_return(g_glob))
		return ;
	replace_dollar(cmd, g_glob);
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		run_pwd(cmd, g_glob);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		cmd_exit(cmd);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		check_arg_env(cmd, g_glob);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		run_export(cmd, g_glob);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		run_unset(cmd, g_glob);
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
		run_echo(cmd, g_glob);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		run_cd(cmd, g_glob);
	else
		run_execve(cmd, g_glob);
}
