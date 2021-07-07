/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadarnau <sadarnau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:31:00 by tpalhol           #+#    #+#             */
/*   Updated: 2020/06/25 14:19:54 by sadarnau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_return(t_glob *g_glob)
{
	ft_putstr_fd("minishell: command not found: ", 1);
	ft_putnbr_fd(g_glob->ret, 1);
	ft_putstr_fd("\n", 1);
	g_glob->ret = 127;
	return (1);
}
