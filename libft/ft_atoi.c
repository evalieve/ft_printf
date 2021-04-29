/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 14:06:55 by evan-der      #+#    #+#                 */
/*   Updated: 2021/03/01 09:29:07 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_changer(const char *str, int i)
{
	int	changed;
	int	result;

	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		changed = str[i] - '0';
		result = (result * 10) + changed;
		i++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	pos_neg;
	int	result;

	i = 0;
	pos_neg = 1;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pos_neg = -1;
		i++;
	}
	if (!(str[i] && str[i] >= '0' && str[i] <= '9'))
		return (0);
	else
		result = ft_changer(str, i);
	return (result * pos_neg);
}
