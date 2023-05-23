/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:54:41 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/16 13:07:09 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*still_dquote(t_token_list **tokens, char *line, t_tools *tools)
{
	int	i;

	if (!line)
		return (NULL);
	i = 0;
	if (*line == '$')
	{
		line = is_dollar_pipe(tokens, line);
		line = afdollar(tokens, line);
	}
	while (line[i] && line[i] != '\"' && line[i] != '$')
		i++;
	addback(tokens, ft_strndup(line, i), WORD);
	line = line + i;
	if (line && *line == 34 && tools->dollar_in == 1)
		line = line + 1;
	return (line);
}

char	*ft_dquotes(t_token_list **tokens, char *line, t_tools *tools)
{
	if (!line)
		return (NULL);
	tools->d_quote = 0;
	tools->dollar_in = 0;
	line = is_dquote(tokens, line, tools);
	while (!ft_strncmp(line, "$$", 2))
	{
		line = is_dollar_pipe(tokens, line);
		line = still_dquote(tokens, line, tools);
	}
	while (line && *line == '$')
	{
		line = is_dollar_pipe(tokens, line);
		line = afdollar(tokens, line);
		line = still_dquote(tokens, line, tools);
	}
	return (line);
}

char	*ft_squotes(t_token_list **tokens, char *line, t_tools *tools)
{
	if (!line)
		return (line);
	tools->s_quote = 0;
	line = is_squote(tokens, line, tools);
	return (line);
}

char	*tokenizer2(char *line, t_token_list **tokens,
		t_tools *tools, char quote)
{
	if (quote == '\'')
	{
		line = ft_squotes(&*tokens, line, tools);
		if (tools->s_quote == 1)
		{
			open_quote_error(&*tokens);
			return (NULL);
		}
	}
	else
	{
		line = ft_dquotes(&*tokens, line, tools);
		if (tools->d_quote == 1)
		{
			open_quote_error(&*tokens);
			return (NULL);
		}
	}
	return (line);
}

t_token_list	*tokenizer(char *line, t_token_list *tokens, t_tools *tools)
{
	if (*line == '\0')
		return (NULL);
	while (line && *line)
	{
		if (ft_strchr("\'", *line) || ft_strchr("\"", *line))
		{
			if (*line == '\'')
				line = tokenizer2(line, &tokens, tools, '\'');
			else
				line = tokenizer2(line, &tokens, tools, '\"');
			if (!line)
				return (NULL);
		}
		else if (ft_strchr(" \t\v\f\r", *line))
			line = is_wspace(&tokens, line);
		else if (ft_strchr("><", *line))
			line = is_redirections(&tokens, line, tools);
		else if (ft_strchr("$|", *line))
			line = is_dollar_pipe(&tokens, line);
		else
			line = is_word(&tokens, line);
	}
	addback(&tokens, "newline", NLINE);
	return (tokens);
}
