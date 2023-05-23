/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:43:04 by abenheni          #+#    #+#             */
/*   Updated: 2023/05/13 10:45:44 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_env(t_env_list **env_list, char *name, char *value)
{
	int			no_created;
	t_env_list	*lst;
	char		*tmp;

	lst = (*env_list);
	no_created = 0;
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			no_created = 1;
			tmp = lst->value;
			lst->value = ft_strjoin_export(lst->value, value);
			free(tmp);
			lst->flag = 0;
			break ;
		}
		lst = lst->next;
	}
	if (!no_created)
		addback_env(env_list, addnew_env(name, value));
}
