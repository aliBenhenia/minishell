/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:16:17 by abenheni          #+#    #+#             */
/*   Updated: 2023/05/14 19:46:40 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*addnew_export(char *var, char *value)
{
	t_export	*new;

	new = malloc(sizeof(t_export));
	if (!new)
		return (NULL);
	if (!ft_strcmp(value, "eq"))
	{
		new->flag = 1;
		new->var = ft_strdup_export(var);
		new->value = ft_strdup_export("\0");
		new->next = NULL;
		return (new);
	}
	new->var = ft_strdup_export(var);
	new->value = ft_strdup_export(value);
	new->next = NULL;
	return (new);
}

void	addback_export(t_export **a, t_export *new)
{
	t_export	*head;

	if ((*a) == NULL)
		(*a) = new;
	else
	{
		head = (*a);
		new->next = NULL;
		head = (*a);
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

t_env_list	*addnew_env(char *var, char *value)
{
	t_env_list	*new;

	new = malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	new->name = ft_strdup_export(var);
	new->value = ft_strdup_export(value);
	new->next = NULL;
	return (new);
}

void	addback_env(t_env_list **a, t_env_list *new)
{
	t_env_list	*head;

	new->next = NULL;
	head = (*a);
	if (head == NULL)
		(*a) = new;
	else
	{
		head = (*a);
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

void	do_env(char *env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr(env[i]);
		ft_putstr("\n");
		i++;
	}
}
