/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_cmd_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:20:34 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/15 12:21:09 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_add_redirect_in(t_cmd *cmd, char *path)
{
	cmd->redirect_in = ft_strdup(path);
}

void	cmd_add_redirect_out(t_cmd *cmd, char *path)
{
	cmd->redirect_out = ft_strdup(path);
}

void	cmd_add_redirect_after(t_cmd *cmd, char *path)
{
	cmd->redirect_after = ft_strdup(path);
}
