/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 23:47:23 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/10 18:19:58 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_last(t_redirections **redirections)
{
	t_redirections	*curr;

	if (!*redirections)
		return (1);
	curr = *redirections;
	while (curr)
	{
		if (curr->type == RIGHTRED || curr->type == APPEND)
			return (0);
		curr = curr->next;
	}
	return (1);
}

int	last_outfile(t_cmd_line **cmd_line, t_redirections **last_out
		, t_redirections **tmp)
{
	t_redirections	*curr;
	int				fd;

	curr = (*cmd_line)->redirections;
	while (curr)
	{
		if (curr == *tmp)
			break ;
		if (curr->type == RIGHTRED || curr->type == APPEND)
		{
			if (curr->type == RIGHTRED)
				fd = open(curr->file, O_CREAT | O_RDWR | O_TRUNC, 0664);
			else
				fd = open(curr->file, O_CREAT | O_RDWR | O_APPEND, 0664);
			if (fd == -1)
			{
				*tmp = curr;
				return (0);
			}
			if (is_last(&curr->next))
				*last_out = curr;
		}
		curr = curr->next;
	}
	return (-1);
}

int	is_last_infile(t_redirections **redirections)
{
	t_redirections	*curr;

	if (!*redirections)
		return (1);
	curr = *redirections;
	while (curr)
	{
		if (curr->type == LEFTRED || curr->type == HEREDOC)
			return (0);
		curr = curr->next;
	}
	return (1);
}

int	last_infile(t_cmd_line **cmd_line, t_redirections **last_in,
		t_redirections **tmp)
{
	t_redirections	*curr;
	int				fd;

	curr = (*cmd_line)->redirections;
	while (curr)
	{
		if (curr->type == LEFTRED || curr->type == HEREDOC)
		{
			if (curr->type == LEFTRED)
				fd = open(curr->file, O_RDONLY, 0777);
			if (fd == -1)
			{
				*tmp = curr;
				return (0);
			}
			if (is_last_infile(&curr->next))
			{
				*last_in = curr;
				return (1);
			}
		}
		curr = curr->next;
	}
	return (-1);
}

int	last_in_out(t_cmd_line **cmd_line, t_redirections **last_in,
		t_redirections **last_out, int flag)
{
	t_redirections	*tmp;

	*last_out = NULL;
	*last_in = NULL;
	if (last_infile(cmd_line, last_in, &tmp) == 0)
	{
		if (last_outfile(cmd_line, last_out, &tmp) == 0)
		{
			if (opendir(tmp->file))
				print_error(tmp->file, ": is a directory\n", 1, flag);
			print_error(tmp->file, ": No such file or directory\n", 1, flag);
		}
		else
			print_error(tmp->file, ": No such file or directory\n", 1, flag);
		return (0);
	}
	if (last_outfile(cmd_line, last_out, &tmp) == 0)
	{
		if (opendir(tmp->file))
			print_error(tmp->file, ": is a directory\n", 1, flag);
		print_error(tmp->file, ": No such file or directory\n", 1, flag);
		return (0);
	}
	return (1);
}
