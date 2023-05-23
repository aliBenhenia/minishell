/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:06:30 by abenheni          #+#    #+#             */
/*   Updated: 2023/05/16 15:19:36 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_number(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '+' || num[i] == '-')
		i++;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

void	not_number_error(char *arg, int flag)
{
	if (flag)
		ft_putstr("exit\n");
	exit_error(arg, "numeric argument required\n", 255);
}

long	ft_atoi_exit(char *str, int flag)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (!(result * sign >= LLONG_MIN && result * sign <= LLONG_MAX)
			|| (sign > 0 && result * sign < 0)
			|| (sign < 0 && result * sign > 0))
			not_number_error(str, flag);
		i++;
	}
	return ((long)result * sign);
}

void	exit_with_arg(char *arg, int flag)
{
	long	exit_status;

	exit_status = ft_atoi_exit(arg, flag);
	if (flag)
		write(2, "exit\n", 5);
	exit ((int)exit_status);
}

void	do_exit(char **s, int flag)
{
	if (!s[1])
	{
		if (flag)
			ft_putstr("exit\n");
		exit(0);
	}
	if (!is_number(s[1]))
		not_number_error(s[1], flag);
	if (is_number(s[1]) && !s[2])
	{
		exit_with_arg(s[1], flag);
	}
	if (is_number(s[1]) && s[2])
	{
		g_var.exit_state = 1;
		write(2, "minishell: exit: too many arguments\n", 36);
		if (!flag)
			exit(g_var.exit_state);
	}
}
