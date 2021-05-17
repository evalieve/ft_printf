#include "../../ft_printf.h"

void	ft_inclwidth_u(char *str, int arg, t_lst *lst)
{
	int	len;

	len = lst->width - ft_countlen(str);
	if (lst->precision == 0 && arg == 0)
	{
		str[0] = '\0';
		len++;
	//	printf("3\n");
	}
	if (lst->dash == 1)
	{
		ft_putstr_fd(str, 1);
		ft_putchar(' ', len);
	//	printf("4\n");
	}
	else
	{
		if (lst->zero == 1)
			ft_putchar('0', len);
		else
			ft_putchar(' ', len);
		ft_putstr_fd(str, 1);
	//	printf("5\n");
	}
	free(str);
}

char	*ft_inclprcsion_u(char *nbr, int prlen)
{
	int		arglen;
//	char	*zeros;
	char	*str;

	arglen = ft_countlen(nbr);
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
	//	printf("1\n");
	}
	//printf("2\n");
	return (nbr);
}

int	ft_specifier_u(va_list args, t_lst *lst)
{
	unsigned int arg;
	char *nbr;

	arg = va_arg(args, int);
	nbr = ft_unsitoa(arg);
	if (!nbr)
		return (0);
	//printf("0\n");
	if (lst->precision > -1)
		lst->zero = 0;
	nbr = ft_inclprcsion_u(nbr, lst->precision);
	if (!nbr)
		return (0);
		//printf("%s\n", nbr);
	ft_inclwidth_u(nbr, arg, lst);
	return (1);
}