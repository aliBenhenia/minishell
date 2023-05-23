/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:20:50 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/16 13:03:18 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_end_of_line(char *line, int i)
{
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	allocate(char *line, t_tools *tools)
{
	tools->i = 0;
	tools->j = 0;
	while (line[tools->i] == ' ')
		tools->i++;
	while (line[tools->i])
	{
		if (line[tools->i] != ' ')
		{
			tools->i++;
			tools->j++;
			tools->k = 0;
		}
		if (line[tools->i] == ' ')
		{
			if (check_end_of_line(line, tools->i))
				break ;
			else if (tools->k == 0)
			{
				tools->j++;
				tools->k = 1;
			}
			tools->i++;
		}
	}
	return (tools->j);
}

void	quotes_checker(char *line, int i, int *flag, int *l)
{
	if ((line[i] == 34 || line[i] == 39) && *flag == 1)
			*flag = 0;
	else if (line[i] == 34 || line[i] == 39)
			*flag = 1;
	*l = 0;
}

char	*remove_additional_spaces2(char *line, int i, int *k, int l)
{
	t_tools	tools;

	tools.new = (char *)ft_malloc(sizeof(char), allocate(line, &tools) + 1);
	while (line[i])
	{
		if (line[i] != ' ')
		{
			quotes_checker(line, i, &tools.flag, &l);
			tools.new[(*k)++] = line[i++];
		}
		else if (line[i] == ' ')
		{
			if (check_end_of_line(line, i))
				break ;
			if (tools.flag == 1)
				tools.new[(*k)++] = line[i];
			else if (l == 0)
			{
				tools.new[(*k)++] = line[i];
				l = 1;
			}
			i++;
		}
	}
	return (tools.new);
}

char	*remove_additional_spaces(char *line)
{
	int		i;
	int		k;
	int		l;
	char	*new;

	i = 0;
	k = 0;
	l = 0;
	while (line[i] == ' ')
		i++;
	new = remove_additional_spaces2(line, i, &k, l);
	new[k] = '\0';
	free(line);
	return (new);
}
