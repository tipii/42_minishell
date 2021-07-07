/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:31:24 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/29 16:25:30 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(t_cmd *cmd)
{
	ft_putstr_fd(cmd->argv[0], 2);
	write(2, ": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, ": ", 2);
	ft_putstr_fd(cmd->argv[1], 2);
	write(1, "\n", 1);
}

void	put_error_3(char *str1, char *str2, char *str3)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
}
