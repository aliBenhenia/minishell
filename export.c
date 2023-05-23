/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:20:21 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/16 15:28:22 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_equal_only(char *str, char **name_value, t_export **export,
	t_env_list **env_list)
{
	if (eqaul_last_only(str) && check_if_exist(name_value[0], *export))
		custom_edit_value(name_value[0], name_value[1], export, env_list);
	else if (check_if_exist(name_value[0], *export))
	{
		free_rows(name_value);
		return ;
	}
	else if (eqaul_last_only(str))
	{
		addback_env(env_list, addnew_env(name_value[0], "\0"));
		addback_export(export, addnew_export(name_value[0], "eq"));
	}
	else
	{
		addback_export(export, addnew_export(name_value[0], name_value[1]));
	}
	free_rows(name_value);
}

void	add_var_in_list(t_export **export, t_env_list **env_list, char *str)
{
	char	**name_value;

	name_value = fill_name_value(str);
	if (!name_value)
		return ;
	if (check_if_equal_is(str) && eqaul_last_only(str) == 0)
	{
		if (check_if_exist(name_value[0], *export))
		{
			if (check_append(str))
			{
				append_free(name_value, export, env_list);
				return ;
			}
			edit_free(name_value, export, env_list);
			return ;
		}
		addback_free(export, env_list, name_value);
	}
	else
	{
		if_equal_only(str, name_value, export, env_list);
		free(name_value);
	}
}

void	print_export(t_export *head)
{
	while (head)
	{
		if (head->flag == 1)
			printf("declare -x %s=\"\"\n", head->var);
		else if (*(head->value) == '\0')
		{
			printf("declare -x %s\n", head->var);
		}
		else
			printf("declare -x %s=\"%s\"\n", head->var, head->value);
		head = head->next;
	}
}

void	edit_env(t_env_list	**env_list, char *name, char *value)
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
			lst->value = ft_strdup_export(value);
			lst->flag = 0;
			return ;
		}
		lst = lst->next;
	}
	if (!no_created)
		addback_env(env_list, addnew_env(name, value));
}

void	do_export(char *str[], t_export **export,
t_env_list **env_list, int flag)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	g_var.exit_state = 0;
	if (str[1] == NULL)
		print_export(*export);
	while (str[i])
	{
		if (correct_name(get_name(str[i])) && !ft_isdigit(str[i][0]))
		{
			add_var_in_list(export, env_list, str[i]);
		}
		else
			error_od_export(str[i]);
		i++;
	}
	sort(export);
	if (flag)
		exit(g_var.exit_state);
}
