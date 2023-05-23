/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:44:42 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/11 19:42:45 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	addback2(t_token_list **tokens, char *value, int type)
{
	t_token_list	*curr;

	curr = *tokens;
	if (!*tokens)
		*tokens = new_token(value, type);
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new_token(value, type);
	}
}

char	*is_squote(t_token_list **tokens, char *line, t_tools *tools)
{
	int	i;

	if (!line)
		return (NULL);
	i = 1;
	while (line[i] && line[i] != '\'')
		i++;
	if (line[i] && line[i] == '\'')
	{
		if (i == 1)
			addback2(tokens, ft_strdup("\0"), WORD);
		else
			addback(tokens, ft_strndup(line + 1, i - 1), WORD);
	}
	else
		tools->s_quote = 1;
	return (line + i + 1);
}

char	*is_dquote(t_token_list **tokens, char *line, t_tools *tools)
{
	int	i;

	if (!line)
		return (NULL);
	i = 1;
	while (line[i] && line[i] != '\"' && line[i] != '$')
		i++;
	if (i == 1 && line[0] == 34 && line[1] != 34)
		tools->dollar_in = 1;
	if (line[i] == '$')
	{
		tools->dollar_in = 1;
		addback(tokens, ft_strndup(line + 1, i - 1), WORD);
		return (line + i);
	}
	if (line[i] && line[i] == '\"')
	{
		if (i == 1)
			addback2(tokens, ft_strdup("\0"), WORD);
		else
			addback(tokens, ft_strndup(line + 1, i - 1), WORD);
	}
	else
		tools->d_quote = 1;
	return (line + i + 1);
}

char	*no_expand(t_token_list **tokens, char	*line, t_tools *tools)
{
	int	i;

	if (!line)
		return (NULL);
	i = 1;
	while (line && line[i] && line[i] != '\"')
		i++;
	if (line && line[i] && line[i] == '\"')
		addback(tokens, ft_strndup(line + 1, i - 1), WORD);
	else
		tools->no_expand = 1;
	return (line + i + 1);
}
