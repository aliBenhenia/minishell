/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:14:56 by mazaroua          #+#    #+#             */
/*   Updated: 2023/05/16 13:17:04 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_export(char *src)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!(new))
		return (NULL);
	while (*src)
		new[i++] = *src++;
	new[i] = '\0';
	return (new);
}

char	*ft_strndup(char *src, int len)
{
	int		i;
	char	*new;

	if (len == 0)
		return (NULL);
	i = 0;
	new = (char *)ft_malloc(1, ft_strlen(src) + 1);
	if (!(new))
		return (NULL);
	while (*src && i < len)
		new[i++] = *src++;
	new[i] = '\0';
	return (new);
}

char	*ft_strndup2(char *src, int len)
{
	int		i;
	char	*new;

	if (len == 0)
		return (NULL);
	i = 0;
	new = malloc(sizeof(char) * len + 1);
	if (!(new))
		return (NULL);
	while (*src && i < len)
		new[i++] = *src++;
	new[i] = '\0';
	return (new);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	free_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > -1)
		free(str[i--]);
	free(str);
}
