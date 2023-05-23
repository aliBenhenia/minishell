/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:23:18 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/06 16:23:57 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_count(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] && s[i] != c)
				i++;
			count += 1;
		}
	}
	return (count);
}

static int	word_length(const char *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

char	*ft_free(char **str)
{
	while (*str)
		free(*str++);
	free(str);
	return (NULL);
}

char	**ft_split1(char **str, char const *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			str[j] = malloc(sizeof(char) * word_length(s, c, i) + 1);
			if (!(str[j]))
				return (ft_free(str), NULL);
			k = 0;
			while (s[i] && s[i] != c)
				str[j][k++] = s[i++];
			str[j++][k] = '\0';
		}
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (!(s))
		return (0);
	str = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!(str))
		return (NULL);
	str = ft_split1(str, s, c);
	return (str);
}
