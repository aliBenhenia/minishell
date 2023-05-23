/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:39:30 by abenheni          #+#    #+#             */
/*   Updated: 2023/05/16 13:04:23 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	found_shlvl(t_env_list **envlist)
{
	t_env_list	*env;

	env = *envlist;
	while (env)
	{
		if (!ft_strcmp("SHLVL", env->name))
			return (1);
		env = env->next;
	}
	return (0);
}

void	increment_shlvl(t_env_list **envlist, t_export **export)
{
	t_env_list	*env;
	t_export	*exp;

	env = *envlist;
	exp = *export;
	while (env)
	{
		if (!ft_strcmp("SHLVL", env->name))
		{
			free(env->value);
			env->value = ft_itoa(ft_atoi(env->value) + 1);
		}
		env = env->next;
	}
	while (exp)
	{
		if (!ft_strcmp("SHLVL", exp->var))
		{
			free(exp->value);
			exp->value = ft_itoa(ft_atoi(exp->value) + 1);
		}
		exp = exp->next;
	}
}

void	ft_shlvl(t_env_list **envlist, t_export **export)
{
	char		**shlvl;

	if (!found_shlvl(envlist))
	{
		shlvl = ft_split("export SHLVL=1", ' ');
		do_export(shlvl, export, envlist, 0);
		free_2d(shlvl);
		return ;
	}
	increment_shlvl(envlist, export);
}
