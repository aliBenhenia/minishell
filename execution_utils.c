/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:13:08 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/11 18:32:07 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_var(t_env_list **env_list)
{
	t_env_list	*envlist;
	char		*home;

	envlist = *env_list;
	home = NULL;
	while (envlist)
	{
		if (!ft_strcmp(envlist->name, "HOME"))
		{
			home = envlist->value;
			return (home);
		}
		envlist = envlist->next;
	}
	return (home);
}

char	**get_path(t_env_list **env_list)
{
	t_env_list	*list;
	char		*path;
	char		**path_splitted;

	list = *env_list;
	while (list)
	{
		if (!(ft_strcmp(list->name, "PATH")))
		{
			path = list->value;
			break ;
		}
		list = list->next;
	}
	path_splitted = ft_split(path, ':');
	return (path_splitted);
}

int	count_list(t_cmd_line **cmd_line)
{
	t_cmd_line	*cmd;
	int			count;

	cmd = *cmd_line;
	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	count_envlist(t_env_list **env_list)
{
	t_env_list	*envlist;
	int			i;

	envlist = *env_list;
	i = 0;
	while (envlist)
	{
		i++;
		envlist = envlist->next;
	}
	return (i);
}

char	**create_envp(t_env_list **env_list)
{
	t_env_list	*envlist;
	char		**envp;
	int			i;
	char		*tmp;

	envlist = *env_list;
	envp = (char **)ft_malloc(sizeof(char *), count_envlist(env_list) + 1);
	i = 0;
	while (envlist)
	{
		tmp = ft_strjoin(envlist->name, "=");
		envp[i] = ft_strjoin(tmp, envlist->value);
		envlist = envlist->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
