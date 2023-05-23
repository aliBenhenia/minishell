/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:17:19 by abenheni          #+#    #+#             */
/*   Updated: 2023/05/16 15:05:24 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_free(char **name_value, t_export **export, t_env_list **env_list)
{
	edit_value(name_value[0], name_value[1], export, env_list);
	free_2d(name_value);
}

void	append_free(char **name_value, t_export **export, t_env_list **env_list)
{
	append_string(name_value[0], name_value[1], export, env_list);
	free_2d(name_value);
}

char	**fill_name_value(char *str)
{
	char	**name_value;

	name_value = malloc(sizeof(char *) * 3);
	if (!name_value)
		return (NULL);
	name_value[0] = get_name(str);
	name_value[1] = get_value(str);
	name_value[2] = NULL;
	return (name_value);
}
