/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:20:07 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/16 14:42:19 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_heredocs(t_cmd_line **cmd_line)
{
	t_redirections	*redirections;
	int				count;

	redirections = (*cmd_line)->redirections;
	count = 0;
	while (redirections)
	{
		if (redirections->type == HEREDOC)
			count++;
		redirections = redirections->next;
	}
	return (count);
}

char	**get_delimiters(t_cmd_line **cmd_line)
{
	t_redirections	*curr;
	char			**delimiters;
	int				i;

	curr = (*cmd_line)->redirections;
	delimiters = (char **)ft_malloc(sizeof(char *),
			(count_heredocs(cmd_line) + 1));
	i = 0;
	while (curr)
	{
		if (curr->type == HEREDOC)
			delimiters[i++] = curr->file;
		curr = curr->next;
	}
	delimiters[i] = NULL;
	return (delimiters);
}

void	heredoc_prompt(char *delimiter, int fd)
{
	char	*buffer;

	while (1337)
	{
		buffer = readline("> ");
		if (!buffer)
		{
			g_var.lastchance = 1;
			break ;
		}
		if (!(ft_strcmp(buffer, delimiter)))
		{
			free(buffer);
			break ;
		}
		buffer = ft_strjoin_heredoc(buffer, "\n");
		write (fd, buffer, ft_strlen(buffer));
	}
}

void	recover_stdin(void)
{
	int	tty_fd;

	if (!ttyname(0))
	{
		tty_fd = open(ttyname(STDOUT_FILENO), O_RDONLY);
		dup2(tty_fd, 0);
		write(1, "\n", 1);
	}
}

int	ft_heredoc(t_cmd_line **cmd_line)
{
	int		i;
	int		fd[2];
	char	**delimiters;

	i = 0;
	delimiters = get_delimiters(cmd_line);
	if (count_heredocs(cmd_line) == 0)
		return (0);
	g_var.heredoc = 1;
	while (i < count_heredocs(cmd_line))
	{
		pipe(fd);
		if (g_var.heredoc == -1)
			break ;
		heredoc_prompt(delimiters[i], fd[1]);
		close(fd[1]);
		i++;
	}
	recover_stdin();
	return (fd[0]);
}
