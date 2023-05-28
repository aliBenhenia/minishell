/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:20:11 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/11 19:43:09 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear(t_token_list	**lst)
{
	t_token_list	*tmp;

	if (!*lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		tmp = tmp->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

void	addback(t_token_list **tokens, char *value, int type)
{
	t_token_list	*curr;

	curr = *tokens;
	if ((!value || !*value))
		return ;
	if (!*tokens)
		*tokens = new_token(value, type);
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new_token(value, type);
	}
}

t_token_list	*new_token(char *value, int type)
{
	t_token_list	*new;

	new = (t_token_list *)ft_malloc(sizeof(t_token_list), 1);
	new->type = type;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	count(char *line)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	j = ft_strlen(line) - 1;
	c = 0;
	while (line[i] && line[i] == 32)
		i++;
	while (line[j] && line[j] == 32)
	{
		j--;
		c++;
	}
	return (c + i);
}

int	all_spaces(char *line, int i)
{
	while (line[i])
	{
		if (line[i] != 32)
			return (0);
		i++;
	}
	return (1);
}
