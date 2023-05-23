/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:38:01 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/16 15:06:30 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status(int size, int *pid)
{
	int	i;

	i = 0;
	while (i < size)
		waitpid(pid[i++], &g_var.exit_state, 0);
	if (WIFEXITED(g_var.exit_state))
		g_var.exit_state = WEXITSTATUS(g_var.exit_state);
	else if (WIFSIGNALED(g_var.exit_state))
		g_var.exit_state = WTERMSIG(g_var.exit_state) + 128;
	g_var.heredoc = -1;
	g_var.i = 0;
}

void	create_pipe(t_cmd_line *cmd_line, int *fd, int *flag)
{
	if (cmd_line->separator == e_pipe)
	{
		pipe(fd);
		*flag = 1;
	}
}

void	ft_dup(t_exec_tools *tools, int **fd,
		t_cmd_line **cmd_line, int fd_heredoc)
{
	if (tools->flg)
		dup_to_pipe(fd, tools->i, count_list(cmd_line));
	if (tools->l_outfile)
		dup_outfile(tools->l_outfile);
	if (tools->l_infile)
		dup_infile(tools->l_infile, fd_heredoc);
}

void	execute_command(t_cmd_line **cmd_line, t_env_list **env_list,
		int **fd, t_export **export)
{
	t_exec_tools	tools;

	tools.cmd_tmp = *cmd_line;
	tools.i = 0;
	tools.flg = 0;
	tools.pid = (int *)ft_malloc(sizeof(pid_t), count_list(cmd_line));
	while (tools.cmd_tmp)
	{
		create_pipe(tools.cmd_tmp, fd[tools.i], &tools.flg);
		tools.fd_heredoc = ft_heredoc(&tools.cmd_tmp);
		if (g_var.heredoc == -1)
			return ;
		tools.pid[tools.i] = fork();
		if (!(tools.pid[tools.i]))
		{
			if (last_in_out(&tools.cmd_tmp, &tools.l_infile,
					&tools.l_outfile, 1) == 0)
				exit(0);
			ft_dup(&tools, fd, cmd_line, tools.fd_heredoc);
			execute_command_2(&tools.cmd_tmp, env_list, export);
		}
		close_pipes(fd, &tools.i, count_list(cmd_line), tools.flg);
		tools.cmd_tmp = tools.cmd_tmp->next;
	}
	exit_status(count_list(cmd_line), tools.pid);
}

void	execution(t_cmd_line **cmd_line,
		t_env_list **env_list, t_export **export_list)
{
	t_redirections	*l_infile;
	t_redirections	*l_outfile;
	int				**fd;
	int				i;

	if ((*cmd_line) && main_builtins(cmd_line)
		&& (*cmd_line)->separator == e_nline)
	{
		ft_heredoc(cmd_line);
		if (g_var.heredoc == -1)
			return ;
		if (last_in_out(cmd_line, &l_infile, &l_outfile, 0) == 0)
			return ;
		execute_builtins(cmd_line, env_list, export_list);
	}
	else if ((*cmd_line))
	{
		fd = (int **)ft_malloc(sizeof(int *), (count_list(cmd_line) - 1));
		i = 0;
		while (i < (count_list(cmd_line) - 1))
			fd[i++] = (int *)ft_malloc(sizeof(int), 2);
		execute_command(cmd_line, env_list, fd, export_list);
	}
}
