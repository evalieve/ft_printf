/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: evan-der <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 18:59:00 by evan-der      #+#    #+#                 */
/*   Updated: 2021/03/01 09:39:20 by evan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int n)
{
	int	len;
	int	result;

	result = 1;
	len = 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	while (len - 1)
	{
		result = result * 10;
		len--;
	}
	return (result);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	len;
	int	cpy;

	if (n == 0)
		return (ft_putchar_fd('0', fd));
	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (n < 0)
	{
		n = n * -1;
		ft_putchar_fd('-', fd);
	}
	len = length(n);
	while (len > 0)
	{
		cpy = n / len;
		ft_putchar_fd((cpy % 10) + '0', fd);
		len = len / 10;
	}
}
