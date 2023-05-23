/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:19:28 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/03 16:08:57 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_node2(t_env_list **env, char *str)
{
	t_env_list	*head;
	t_env_list	*temp;

	head = (*env);
	if (head == NULL)
		return ;
	if (head != NULL && ft_strcmp(head->name, str) == 0)
	{
		temp = (*env);
		(*env) = (*env)->next;
		free_unset_env(temp);
		return ;
	}
	while (head != NULL && head->next != NULL)
	{
		if (ft_strcmp(head->next->name, str) == 0)
		{
			temp = head->next;
			head->next = temp->next;
			free_unset_env(temp);
		}
		else
			head = head->next;
	}
}

void	rm_node(t_export **export, char *str)
{
	t_export	*head;
	t_export	*temp;

	head = (*export);
	if (head == NULL)
		return ;
	if (head != NULL && ft_strcmp(head->var, str) == 0)
	{
		temp = (*export);
		(*export) = (*export)->next;
		free_unset_export(temp);
		return ;
	}
	while (head != NULL && head->next != NULL)
	{
		if (ft_strcmp(head->next->var, str) == 0)
		{
			temp = head->next;
			head->next = temp->next;
			free_unset_export(temp);
		}
		else
			head = head->next;
	}
}

int	check_name_is_exist(char *s, t_export *export)
{
	t_export	*head;

	head = export;
	while (head)
	{
		if (ft_strcmp(head->var, s) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}

void	error_of_unset(char *s)
{
	g_var.exit_state = 1;
	printf("bash: unset: `%s' not a valid identifier\n", s);
}

void	do_unset(char *str[], t_export **data, t_env_list **env_list, int flag)
{
	int	i;

	g_var.exit_state = 0;
	if (str[1] == NULL)
		return ;
	i = 1;
	while (str[i])
	{
		if (check_name_is_exist(str[i], (*data)))
		{
			rm_node(data, str[i]);
			rm_node2(env_list, str[i]);
		}
		else if (!correct_name_unset(str[i]) || ft_isdigit(str[i][0]))
			error_of_unset(str[i]);
		i++;
	}
	if (flag)
		exit(g_var.exit_state);
}
