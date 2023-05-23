/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:46:03 by abenheni          #+#    #+#             */
/*   Updated: 2023/05/10 18:22:55 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '-' && s[i + 1] == '\0')
		return (0);
	if (s[i] != '-')
		return (0);
	i++;
	while (s[i] && s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

void	ft_echo(char **str, int flag)
{
	int	is_line;
	int	i;

	i = 1;
	is_line = 0;
	while (check_n(str[i]))
	{
		is_line = 1;
		i++;
	}
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (is_line == 0)
		printf("\n");
	g_var.exit_state = 0;
	if (flag)
		exit(g_var.exit_state);
}
