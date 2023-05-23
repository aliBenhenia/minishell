/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:29:16 by abenheni          #+#    #+#             */
/*   Updated: 2023/05/14 18:00:28 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_equal_is(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1])
			return (1);
		i++;
	}
	return (0);
}

int	check_if_exist(char *name, t_export *export)
{
	t_export	*head;

	head = export;
	while (head)
	{
		if (ft_strcmp(head->var, name) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}

char	*get_name(char *s)
{
	int		i;

	i = 0;
	if (s[0] == '=')
		return (NULL);
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			break ;
		else if (s[i] == '+' && s[i + 1] == '+')
			return (NULL);
		i++;
	}
	return (ft_strndup2(s, i));
}

char	*get_value(char *s)
{
	int		i;
	int		f;

	i = 0;
	f = 0;
	while (s[i] && s[i] != '=')
		i++;
	i++;
	return (ft_strndup2(s + i, ft_strlen(s)));
}

void	edit_value(char *name, char *value, t_export **data,
	t_env_list **env_list)
{
	t_export	*head;

	head = (*data);
	while (head)
	{
		if (ft_strcmp(head->var, name) == 0)
		{
			if (!ft_strcmp(head->value, value))
				return ;
			free(head->value);
			head->value = ft_strdup_export(value);
			head->flag = 0;
			break ;
		}
		head = head->next;
	}
	edit_env(env_list, name, value);
}
