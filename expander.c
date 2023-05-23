/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 00:26:22 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/16 12:55:34 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	var_not_found2(t_token_list *head, t_token_list *tmp, t_token_list *var)
{
	while (head && head->type != NLINE)
	{
		if (head->next->next && head->next->next->type == DOLLAR)
		{
			tmp = head;
			head = head->next->next->next;
			if (!ft_strcmp(head->value, var->value) && var->type == head->type)
			{
				tmp->next = head->next;
				return ;
			}
		}
		else
			head = head->next;
	}
}

void	var_not_found(t_token_list **tokens, t_token_list *var)
{
	t_token_list	*head;
	t_token_list	*tmp;

	head = *tokens;
	tmp = NULL;
	if ((*tokens)->type == DOLLAR
		&& !ft_strcmp((*tokens)->next->value, var->value))
	{
		(*tokens) = (*tokens)->next->next;
		if ((*tokens)->type == SPACE)
			(*tokens) = (*tokens)->next;
		return ;
	}
	var_not_found2(head, tmp, var);
}

void	expand2(t_token_list **tokens, t_env_list **env, int flag)
{
	t_env_list		*envlist;
	t_token_list	*token;

	token = *tokens;
	while (token && token->type != NLINE)
	{
		if (token && token->type == AFDOLLAR)
		{
			flag = 0;
			envlist = *env;
			while (envlist)
			{
				if (!ft_strcmp(token->value, envlist->name))
				{
					token->value = envlist->value;
					flag = 1;
				}
				envlist = envlist->next;
			}
			if (flag == 0)
				var_not_found(tokens, token);
		}
		token = token->next;
	}
}

void	expand(t_token_list **tokens, t_env_list **env)
{
	int				flag;

	flag = 0;
	if (!*tokens || (*tokens)->type == NLINE)
		return ;
	expand2(tokens, env, flag);
}
