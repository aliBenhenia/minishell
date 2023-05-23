/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:59:37 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/16 14:55:18 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrlc_2(void)
{
	if ((g_var.heredoc != -1 && g_var.i == 1) || (g_var.lastchance == 1))
	{
		if (g_var.lastchance == 1)
		{
			g_var.heredoc = -1;
			g_var.i = -1;
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctrlc(int sig)
{
	int	flag;

	(void)sig;
	flag = 0;
	g_var.exit_state = 1;
	if (g_var.heredoc == 1)
	{
		close(0);
		g_var.heredoc = -1;
		g_var.i = 1;
		return ;
	}
	if (waitpid(-1, 0, WNOHANG) == 0)
		flag = 1;
	else
		flag = 0;
	if (flag == 1)
		return ;
	ctrlc_2();
}
