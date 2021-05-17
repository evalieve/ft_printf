#include "../../ft_printf.h"

void	ft_inclwidth_di(char *str, int arg, t_lst *lst)
{
	int	len;

	len = lst->width - ft_countlen(str);
	if (lst->precision == 0 && arg == 0)
	{
		str[0] = '\0';
		len++;
	}
	if (lst->dash == 1)
	{
		ft_putstr_fd(str, 1);
		ft_putchar(' ', len);
	}
	else
	{
		if (lst->zero == 1)
			ft_putchar('0', len);
		else
			ft_putchar(' ', len);
		ft_putstr_fd(str, 1);
	}
	free(str);
}

char	*ft_inclprcsion_di(char *nbr, int prlen, int neg)
{
	int		arglen;
	char	*zeros;
	char	*str;

	if (nbr[0] == '-')
		neg++;
	arglen = ft_countlen(&nbr[neg]);
	if (prlen > arglen)
	{
		zeros = ft_calloc(prlen - arglen + 1 + neg, sizeof(char));
		if (!zeros)
			return (0);
		zeros[0] = '-';
		while (prlen - arglen > 0)
		{
			prlen--;
			zeros[prlen - arglen + neg] = '0';
		}
		str = ft_fstrjoin(zeros, nbr, neg);
		if (!str)
			return (0);
		return (str);
	}
	return (nbr);
}

int	ft_specifier_di(va_list args, t_lst *lst)
{
	char	*nbr;
	int		arg;
	int		neg;

	neg = 0;
	arg = va_arg(args, int);
	nbr = ft_itoa(arg);
	if (!nbr)
		return (0);
	nbr = ft_inclprcsion_di(nbr, lst->precision, neg);
	if (!nbr)
		return (0);
	if (lst->precision > -1)
		lst->zero = 0;
	ft_inclwidth_di(nbr, arg, lst);
	return (1);
}
