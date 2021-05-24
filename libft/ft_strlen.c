/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:43:25 by evan-der      #+#    #+#                 */
/*   Updated: 2021/03/01 09:41:50 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	//printf("strlen = %s\n", s);
	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		i++;
	//	printf("while loop = %d\n", i);
	}
	return (i);
}
