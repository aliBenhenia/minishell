/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:40:48 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/16 13:12:30 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_wspace(t_token_list **tokens, char *line)
{
	int	i;

	if (!line)
		return (NULL);
	i = 0;
	while (ft_strchr(" \t\v\f\r", line[i]) && line[i])
		i++;
	addback(tokens, " ", SPACE);
	return (line + i);
}

char	*is_dollar_pipe(t_token_list **tokens, char *line)
{
	if (!line)
		return (NULL);
	if (*line == '$')
	{
		if (*(line + 1) == '?')
		{
			addback(tokens, ft_itoa_free(g_var.exit_state), WORD);
			return (line + 2);
		}
		if (*(line + 1) == '$')
		{
			addback(tokens, "$$", WORD);
			return (line + 2);
		}
		addback(tokens, "$", DOLLAR);
		line = afdollar(tokens, line + 1);
		return (line);
	}
	else if (*line == '|')
	{
		addback(tokens, "|", PIPE);
		return (line + 1);
	}
	return (0);
}

char	*is_word(t_token_list **tokens, char *line)
{
	int		i;
	char	*word;

	if (!line)
		return (NULL);
	i = 0;
	while (!ft_strchr(" \t\v\f\r><|$\'\"", line[i]))
		i++;
	word = ft_strndup(line, i);
	addback(tokens, word, WORD);
	return (line + i);
}

char	*afdollar(t_token_list **tokens, char *line)
{
	int		i;
	int		j;
	char	*afdollar;

	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if ((line[i] != 34) && (ft_isalnum(line[i]) || line[i] == '_'))
			i++;
		else
			break ;
	}
	afdollar = (char *)ft_malloc(1, i + 1);
	while (j < i)
	{
		afdollar[j] = line[j];
		j++;
	}
	afdollar[j] = '\0';
	addback(tokens, afdollar, AFDOLLAR);
	return (line + i);
}
