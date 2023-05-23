/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:46:10 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/16 13:12:27 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_quote_error(t_token_list **tokens)
{
	g_var.exit_state = 258;
	write(1, "Syntax error: Open quote\n",
		ft_strlen("Syntax error: Open quote\n"));
	*tokens = NULL;
}

int	count_var_len(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] != 34) && (ft_isalnum(line[i]) || line[i] == '_'))
			i++;
		else
			break ;
	}
	return (i);
}

char	*is_redirections2(t_token_list **tokens, char *line, t_tools *tools)
{
	addback(tokens, "<<", HEREDOC);
	line = is_wspace(tokens, line + 2);
	while (*line == 34)
	{
		tools->no_expand = 0;
		line = no_expand(tokens, line, tools);
		if (tools->no_expand == 1)
		{
			open_quote_error(tokens);
			return (NULL);
		}
	}
	if (*line == '$')
	{
		addback(tokens, ft_strndup(line, count_var_len(line + 1) + 1), WORD);
		line = line + count_var_len(line + 1) + 1;
	}
	return (line);
}

char	*is_redirections(t_token_list **tokens, char *line, t_tools *tools)
{
	if (!line)
		return (NULL);
	if (*line == '>')
	{
		if (*(line + 1) == '>')
		{
			addback(tokens, ">>", APPEND);
			return (line + 2);
		}
		addback(tokens, ">", RIGHTRED);
	}
	else if (*line == '<')
	{
		if (*(line + 1) == '<')
		{
			line = is_redirections2(tokens, line, tools);
			return (line);
		}
		addback(tokens, "<", LEFTRED);
	}
	return (line + 1);
}
