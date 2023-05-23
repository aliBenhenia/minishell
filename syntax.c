/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 00:01:28 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/12 15:22:57 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirections_syntax(t_token_list **tokens)
{
	t_token_list	*tokens_;

	tokens_ = *tokens;
	while (tokens_ && tokens_->type != NLINE)
	{
		if (tokens_ && (tokens_->type == RIGHTRED || tokens_->type == LEFTRED
				|| tokens_->type == APPEND || tokens_->type == HEREDOC))
		{
			if (tokens_ && (tokens_->next && tokens_->next->type == SPACE))
				tokens_ = tokens_->next;
			if (tokens_ && (tokens_->next->type == NLINE
					|| tokens_->next->type != WORD))
			{
				g_var.exit_state = 258;
				printf("minishell: syntax error near unexpected token `%s'\n",
					tokens_->next->value);
				return (0);
			}
		}
		tokens_ = tokens_->next;
	}
	return (1);
}

int	pipe_syntax(t_token_list **tokens)
{
	t_token_list	*tokens_;

	tokens_ = *tokens;
	if (tokens_->type == PIPE)
	{
		g_var.exit_state = 258;
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	while (tokens_->type != NLINE)
	{
		if (tokens_->type == PIPE)
		{
			if (tokens_->next && tokens_->next->type == SPACE)
				tokens_ = tokens_->next;
			if (tokens_->next->type == NLINE || tokens_->next->type == PIPE)
			{
				g_var.exit_state = 258;
				printf("minishell: syntax error near unexpected token `|'\n");
				return (0);
			}
		}
		tokens_ = tokens_->next;
	}
	return (1);
}

int	heredoc_syntax(t_token_list **tokens)
{
	t_token_list	*token;

	token = *tokens;
	while (token && token->type != NLINE)
	{
		if (token->type == HEREDOC)
		{
			token = token->next;
			if (token && token->type == SPACE)
				token = token->next;
			if (token && token->type != DOLLAR && token->type != WORD)
			{
				g_var.exit_state = 258;
				printf("minishell: syntax error near unexpected token `%s'\n",
					token->value);
				return (0);
			}
		}
		token = token->next;
	}
	return (1);
}

int	syntax(t_token_list *tokens)
{
	if (!tokens || tokens->type == NLINE)
		return (0);
	if (redirections_syntax(&tokens) && pipe_syntax(&tokens))
		return (1);
	return (0);
}
