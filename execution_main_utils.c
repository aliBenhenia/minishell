/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 22:31:13 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/16 16:30:46 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_to_pipe(int **fd, int i, int cmds)
{
	if (i == 0)
	{
		dup2(fd[i][1], 1);
		close(fd[i][0]);
		close(fd[i][1]);
	}
	else if (i + 1 == cmds)
	{
		dup2(fd[i - 1][0], 0);
		close(fd[i - 1][0]);
	}
	else if (i > 0 && i + 1 < cmds)
	{
		dup2(fd[i - 1][0], 0);
		dup2(fd[i][1], 1);
		close(fd[i - 1][0]);
		close(fd[i][1]);
		close(fd[i][0]);
	}
}

void	execute_command_2(t_cmd_line **cmd_line,
	t_env_list **env_list, t_export **export)
{
	int	built_code;

	built_code = builtins((*cmd_line)->str[0]);
	signal(SIGQUIT, SIG_DFL);
	if (built_code)
		exec_builtins((*cmd_line)->str, env_list, built_code, export);
	else
		execve_func((*cmd_line)->str, env_list);
}

char	*check_command_in_path(char **path, char *cmd)
{
	int	i;

	i = 0;
	cmd = ft_strjoin("/", cmd);
	while (path[i])
	{
		if (!access(ft_strjoin(path[i], cmd), F_OK))
		{
			return (ft_strjoin(path[i], cmd));
			break ;
		}
		if (access(ft_strjoin(path[i], cmd), X_OK) == -1)
		i++;
	}
	return (NULL);
}

void	print_error(char *cmd, char *error, int exit_status, int flag)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(error, 2);
	if (flag)
		exit(exit_status);
}

void	execve_func(char **cmd, t_env_list **env_list)
{
	char	**path;
	char	*cmd_;
	char	**envp;

	path = get_path(env_list);
	cmd_ = check_command_in_path(path, cmd[0]);
	free_2d(path);
	envp = create_envp(env_list);
	if (ft_strchr(cmd[0], '/'))
	{
		if (opendir(cmd[0]))
			print_error(cmd[0], ": is a directory\n", 126, 1);
		if (execve(cmd[0], cmd, envp) == -1)
		{
			if (access(cmd[0], F_OK) == -1)
				print_error(cmd[0], " :No such file or directory\n", 127, 1);
			else
			{
				if (access(cmd[0], X_OK) == -1)
					print_error(cmd[0], " :Permission denied\n", 126, 1);
			}
		}
	}
	else if (execve(cmd_, cmd, envp) == -1)
		print_error(cmd[0], ": command not found\n", 127, 1);
}
