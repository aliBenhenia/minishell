/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:19:42 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/12 19:41:18 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*addnew1(char *var, char *value)
{
	t_export	*new;

	new = malloc(sizeof(t_export));
	if (!new)
		return (NULL);
	new->var = var;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	addback_export1(t_export **a, t_export *new)
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

t_env_list	*addnew2_1(char *var, char *value)
{
	t_env_list	*new;

	new = malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	new->name = var;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	addback_env2(t_env_list **a, t_env_list *new)
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

void	init_env(t_export **export, t_env_list **env_list, char **env)
{
	int			i;
	char		**var_val;
	char		**var_val2;
	t_export	*new;
	t_env_list	*new1;

	i = 0;
	while (env && env[i])
	{
		var_val = split_env_var(env[i]);
		var_val2 = split_env_var(env[i]);
		new = addnew1(var_val[0], var_val[1]);
		addback_export1(export, new);
		new1 = addnew2_1(var_val2[0], var_val2[1]);
		addback_env2(env_list, new1);
		free(var_val);
		free(var_val2);
		i++;
	}
	sort(export);
}
