#include "../../ft_printf.h"

void	ft_inclwidth_s(char *str, t_lst *lst, int strlen)
{
	int wlen;

	wlen = lst->width - strlen;
	if (wlen > 0)
	{
		if (lst->dash)
		{
			ft_putstr_fd(str, 1);
			ft_putchar(' ', wlen);
		}
		else
		{
			ft_putchar(' ', wlen);
			ft_putstr_fd(str, 1);
		}
	}
	else
		ft_putstr_fd(str, 1);
}

char	*ft_inclprcsion_s(char *str, int arglen, int prlen)
{
	char	*dup;

	if (prlen < arglen)
	{
		dup = ft_calloc(prlen + 1, sizeof(char));
		ft_strlcpy(dup, str, prlen + 1);
		return (dup);
	}
	return (str);
}

int	ft_specifier_s(va_list args, t_lst *lst)
{
	char *str;
	int arglen;

	str = va_arg(args, char *);
	arglen = ft_strlen(str);
	str = ft_inclprcsion_s(str, arglen, lst->precision);
	arglen = ft_strlen(str);
	ft_inclwidth_s(str, lst, arglen);
	return (1);
}