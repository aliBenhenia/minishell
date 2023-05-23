/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:29:26 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/11 18:18:58 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_alloc2(t_token_list **tokens, int *i)
{
	if ((*tokens)->type == RIGHTRED || (*tokens)->type == LEFTRED
		|| (*tokens)->type == APPEND || (*tokens)->type == HEREDOC)
	{
		(*tokens) = (*tokens)->next;
		if ((*tokens)->type == SPACE)
			(*tokens) = (*tokens)->next;
		if ((*tokens)->type == WORD)
			(*tokens) = (*tokens)->next;
	}
	if ((*tokens) && ((*tokens)->type == SPACE))
		(*tokens) = (*tokens)->next;
	if ((*tokens) && ((*tokens)->type == WORD || (*tokens)->type == DOLLAR))
	{
		if ((*tokens)->type == DOLLAR)
			(*tokens) = (*tokens)->next;
		while ((*tokens))
		{
			if (((*tokens)->type == WORD || (*tokens)->type == AFDOLLAR)
				|| (*tokens)->type == DOLLAR)
				(*tokens) = (*tokens)->next;
			else
				break ;
		}
		*i += 1;
	}
}

int	to_alloc_count(t_token_list **tokens)
{
	t_token_list	*tokens_;
	int				i;

	tokens_ = *tokens;
	i = 0;
	while (tokens_ && tokens_->type != PIPE && tokens_->type != NLINE)
		to_alloc2(&tokens_, &i);
	return (i);
}

void	*parser(t_cmd_line **cmd_line, t_token_list *tokens)
{
	t_tools	tools;

	if (!tokens || tokens->type == NLINE)
		return (NULL);
	while (tokens)
	{
		tools.i = 0;
		tools.tmp = NULL;
		tools.str = (char **)ft_malloc(sizeof(char *),
				(to_alloc_count(&tokens) + 1));
		tools.str[to_alloc_count(&tokens)] = NULL;
		tools.redirections = NULL;
		if (tokens && tokens->type == SPACE)
			tokens = tokens->next;
		while (tokens && tokens->type != PIPE && tokens->type != NLINE)
		{
			parser_word(&tokens, &tools.str, &tools.tmp, &tools.i);
			parser_redirections(&tokens, &tools.redirections);
			parser_space(&tokens, &tools.tmp, &tools.i);
		}
		if (tokens && (tokens->type == NLINE || tokens->type == PIPE))
			parser_cmd_line(cmd_line, &tokens, tools.str, tools.redirections);
	}
	return (NULL);
}
