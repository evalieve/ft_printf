#include "../../ft_printf.h"

char	*ft_inclprcsion_Xx(char *str, int strlen, int prlen)
{
	char	*new;

	if (prlen > strlen)
	{
		new = ft_calloc(prlen - strlen + 1, sizeof(char));
		if (!new)
			return (0);
		while (prlen - strlen > 0)
		{
			prlen--;
			new[prlen - strlen] = '0';
		}
		new = ft_fstrjoin(new, str, 0);
		if (!new)
			return (0);
		return (new);
	}
	return (str);
}

int	ft_devider(unsigned long num)
{
	int	len;

	len = 0;
	if (num == 0)
		len++;
	while (num)
	{
		num = num / 16;
		len++;
	}
	return (len);
}

char	*ft_hexitoa(unsigned long num, char type)
{
	int				len;
	unsigned long	numdup;
	char			*str;

	len = ft_devider(num);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	str[0] = '0';
	while (num)
	{
		len--;
		numdup = num / 16;
		num = num % 16;
		if (num >= 0 && num <= 9)
			str[len] = num + '0';
		else if (num >= 10 && num <= 15)
			str[len] = num - 10 + type;
		num = numdup;
	}
	return (str);
}

int	ft_specifier_Xx(va_list args, t_lst *lst)
{
	unsigned int	arg;
	char			*str;
	char			type;
	int				strlen;
	int				len;

	type = 'a';
	if (*lst->specifier == 'X')
		type = 'A';
	arg = va_arg(args, unsigned int);
	str = ft_hexitoa(arg, type);
	if (!str)
		return (-1);
	str = ft_inclprcsion_Xx(str, ft_strlen(str), lst->precision);
	if (!str)
		return (-1);
	if (arg == 0 && lst->precision == 0)
		strlen = 0;
	else
		strlen = ft_strlen(str);
	len = lst->width - strlen;
	if (len < 0)
		len = 0;
	ft_inclwidth_upXx(str, arg, lst, len);
	return (strlen + len);
}
