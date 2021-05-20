#include "../../ft_printf.h"

void	ft_inclwidth_u(char *str, int arg, t_lst *lst, int len)
{
	if (lst->precision == 0 && arg == 0)
		str[0] = '\0';
	if (lst->dash == 1)
	{
		ft_putstr_fd(str, 1);
		ft_putchar(' ', len);
	}
	else
	{
		if (lst->zero == 1 && lst->precision == -1)
			ft_putchar('0', len);
		else
			ft_putchar(' ', len);
		ft_putstr_fd(str, 1);
	}
	free(str);
}

char	*ft_inclprcsion_u(char *nbr, int prlen)
{
	int		arglen;
	char	*str;

	arglen = ft_strlen(nbr);
	if (prlen > arglen)
	{
		str = ft_calloc(prlen - arglen + 1, sizeof(char));
		if (!str)
			return (0);
		while (prlen - arglen > 0)
		{
			prlen--;
			str[prlen - arglen] = '0';
		}
		str = ft_fstrjoin(str, nbr, 0);
		if (!str)
			return (0);
		return (str); 
	}
	return (nbr);
}

int	ft_specifier_u(va_list args, t_lst *lst)
{
	unsigned int arg;
	char *nbr;
	int strlen;
	int len;

	arg = va_arg(args, int);
	nbr = ft_unsitoa(arg);
	if (!nbr)
		return (0);
	nbr = ft_inclprcsion_u(nbr, lst->precision);
	if (!nbr)
		return (0);
	if (lst->precision == 0 && arg == 0)
		strlen = 0;
	else
		strlen = ft_strlen(nbr);
	len = lst->width - strlen;
	if (len < 0)
		len = 0;
	ft_inclwidth_u(nbr, arg, lst, len);
	return (len + strlen);
}