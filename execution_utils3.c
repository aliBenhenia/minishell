/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:22:46 by abenheni          #+#    #+#             */
/*   Updated: 2023/05/16 13:27:37 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(int **fd, int *i, int cmds, int flag)
{
	if (flag != 1)
		return ;
	if (*i == 0)
		close(fd[*i][1]);
	else if ((*i) + 1 == cmds)
		close(fd[(*i) - 1][0]);
	else if ((*i) > 0 && (*i) + 1 < cmds)
	{
		close(fd[*i][1]);
		close(fd[(*i) - 1][0]);
	}
	*i += 1;
}
