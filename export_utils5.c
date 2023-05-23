/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenheni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:53:59 by abenheni          #+#    #+#             */
/*   Updated: 2023/05/14 18:54:01 by abenheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	addback_free(t_export **export,
		t_env_list **env_list, char **name_value)
{
	addback_export(export, addnew_export(name_value[0], name_value[1]));
	addback_env2(env_list, addnew_env(name_value[0], name_value[1]));
	free_2d(name_value);
}

void	custom_edit_env(t_env_list	**env_list, char *name, char *value)
{
	t_env_list	*lst;
	int			no_created;

	no_created = 0;
	lst = (*env_list);
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			no_created = 1;
			free(lst->value);
			lst->value = ft_strdup_export("");
			lst->flag = 1;
			return ;
		}
		lst = lst->next;
	}
	if (!no_created)
		addback_env2(env_list, addnew_env(name, value));
}

void	custom_edit_value(char *name, char *value, t_export **data,
	t_env_list **env_list)
{
	t_export	*head;

	head = (*data);
	while (head)
	{
		if (ft_strcmp(head->var, name) == 0)
		{
			free(head->value);
			head->value = ft_strndup2("", 1);
			head->flag = 1;
			break ;
		}
		head = head->next;
	}
	custom_edit_env(env_list, name, value);
}

void	free_rows(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > -1)
		free(str[i--]);
}
