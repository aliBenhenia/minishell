/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:21:12 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/11 18:21:31 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirections	*init_redirection(int type, char *file)
{
	t_redirections	*redirection_node;

	redirection_node = (t_redirections *)ft_malloc(sizeof(t_redirections), 1);
	redirection_node->type = type;
	redirection_node->file = file;
	redirection_node->next = NULL;
	return (redirection_node);
}

void	fill_redirections_list(t_redirections **redirections,
		t_redirections *new)
{
	t_redirections	*curr;

	if (!new)
		return ;
	curr = *redirections;
	if (!*redirections)
		*redirections = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	separator(t_cmd_line *cmd, t_token_list *token)
{
	if (token->type == NLINE)
		cmd->separator = e_nline;
	else if (token->type == PIPE)
		cmd->separator = e_pipe;
}

t_cmd_line	*init_cmdline(char **str, t_redirections *redirections,
		t_token_list *token)
{
	t_cmd_line	*cmd;

	cmd = (t_cmd_line *)ft_malloc(sizeof(t_cmd_line), 1);
	cmd->str = str;
	cmd->redirections = redirections;
	separator(cmd, token);
	cmd->next = NULL;
	return (cmd);
}

void	fill_cmd_line(t_cmd_line **cmdline, t_cmd_line *new)
{
	t_cmd_line	*curr;

	if (!new)
		return ;
	curr = *cmdline;
	if (!*cmdline)
		*cmdline = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}
