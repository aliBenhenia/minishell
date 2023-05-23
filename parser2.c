/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:30:26 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/12 17:16:10 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_word(t_token_list **tokens, char ***str, char **tmp, int *i)
{
	if ((*tokens)->type == WORD || (*tokens)->type == DOLLAR)
	{
		if ((*tokens)->type == WORD || (*tokens)->type == DOLLAR)
		{
			if ((*tokens)->type == DOLLAR && (*tokens)->next->type == AFDOLLAR)
				*tokens = (*tokens)->next;
			if (!(*tmp))
				*tmp = (*tokens)->value;
			else
				*tmp = ft_strjoin(*tmp, (*tokens)->value);
			(*str)[*i] = *tmp;
			*tokens = (*tokens)->next;
		}
	}
}

void	parser_redirections(t_token_list **tokens,
		t_redirections **redirections)
{
	char	*tmp;
	int		type;

	if (tokens && ((*tokens)->type == RIGHTRED || (*tokens)->type == LEFTRED
			|| (*tokens)->type == APPEND || (*tokens)->type == HEREDOC))
	{
		type = (*tokens)->type;
		if ((*tokens) && (*tokens)->next->type == SPACE)
			(*tokens) = (*tokens)->next;
		if ((*tokens)->next->type == WORD)
		{
			*tokens = (*tokens)->next;
			while ((*tokens)->type == WORD)
			{
				tmp = ft_strjoin(tmp, (*tokens)->value);
				*tokens = (*tokens)->next;
			}
			fill_redirections_list(&*redirections, init_redirection(type, tmp));
		}	
		if ((*tokens) && (*tokens)->type == SPACE)
			(*tokens) = (*tokens)->next;
	}
}

void	parser_space(t_token_list **tokens, char **tmp, int *i)
{
	if (*tokens && (*tokens)->type == SPACE)
	{
		if ((*tokens)->next->type != NLINE && (*tokens)->next->type != PIPE)
			*i += 1;
		*tokens = (*tokens)->next;
		*tmp = NULL;
	}
}

void	parser_cmd_line(t_cmd_line **cmd_line, t_token_list **tokens,
		char **str, t_redirections *redirections)
{
	fill_cmd_line(cmd_line, init_cmdline(str, redirections, *tokens));
	*tokens = (*tokens)->next;
}
