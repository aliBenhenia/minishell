/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenheni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 20:15:07 by abenheni          #+#    #+#             */
/*   Updated: 2023/05/14 20:15:08 by abenheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_unset_env(t_env_list *temp)
{
	free(temp->name);
	free(temp->value);
	free(temp);
}

void	free_unset_export(t_export *temp)
{
	free(temp->var);
	free(temp->value);
	free(temp);
}

int	correct_name_unset(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (ft_isalnum(s[i]) == 0)
		{
			if (s[i] == '+' && s[i + 1] == '\0' && i != 0)
				return (0);
			return (0);
		}
		i++;
	}
	return (1);
}
