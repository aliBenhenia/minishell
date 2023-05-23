/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:26:43 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/16 14:52:38 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_var;

void	body(char *line, t_export **export_list, t_env_list **env_list)
{
	t_token_list	*tokens;
	t_cmd_line		*cmd_line;
	t_tools			tools;

	cmd_line = NULL;
	tokens = NULL;
	tokens = tokenizer(line, tokens, &tools);
	if (tokens && syntax(tokens))
	{
		expand(&tokens, env_list);
		parser(&cmd_line, tokens);
		execution(&cmd_line, env_list, export_list);
	}
	free_all();
}

char	*prompt(void)
{
	char	*line;

	line = readline("\x1B[36m""minishell$ ""\001\e[0m\002");
	if (!line)
	{
		ft_putstr("exit\n");
		exit(0);
	}
	add_history(line);
	line = remove_additional_spaces(line);
	return (line);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_export	*export_list;
	t_env_list	*env_list;

	(void)ac;
	(void)av;
	export_list = NULL;
	env_list = NULL;
	g_var.allocated = NULL;
	init_env(&export_list, &env_list, env);
	ft_shlvl(&env_list, &export_list);
	while (1)
	{
		g_var.heredoc = 0;
		signal(SIGINT, &ctrlc);
		signal(SIGQUIT, SIG_IGN);
		line = prompt();
		if (line)
			body(line, &export_list, &env_list);
	}
}
