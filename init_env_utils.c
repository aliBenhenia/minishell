/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:28:43 by abenheni          #+#    #+#             */
/*   Updated: 2023/05/16 13:16:53 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(t_export *a, t_export *b)
{
	char	*temp_var;
	char	*temp_value;
	int		temp_flag;

	temp_var = a->var;
	temp_value = a->value;
	temp_flag = a->flag;
	a->var = b->var;
	a->value = b->value;
	a->flag = b->flag;
	b->var = temp_var;
	b->value = temp_value;
	b->flag = temp_flag;
}

void	sort(t_export **head)
{
	t_export	*current;
	int			flag_swapped;

	flag_swapped = 1;
	if (!*head)
		return ;
	while (flag_swapped)
	{
		flag_swapped = 0;
		current = *head;
		while (current->next != NULL)
		{
			if (ft_strcmp(current->var, current->next->var) > 0)
			{
				swap(current, current->next);
				flag_swapped = 1;
			}
			current = current->next;
		}
	}
}

char	**split_env_var(char *env)
{
	char	**splitted;
	int		i;

	splitted = malloc(sizeof(char *) * 3);
	i = 0;
	while (env[i] != '=')
		i++;
	splitted[0] = ft_strndup2(env, i);
	splitted[1] = ft_strndup2(env + i + 1, ft_strlen(env));
	return (splitted);
}
