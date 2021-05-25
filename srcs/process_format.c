#include "../ft_printf.h"

int	ft_checker(const char *s, va_list args, t_lst *lst)
{
	int	print;

	if (*s == 'd' || *s == 'i')
		print = ft_specifier_di(args, lst);
	if (*s == 'c')
		print = ft_specifier_c(args, lst);
	if (*s == 'u')
		print = ft_specifier_u(args, lst);
	if (*s == 's')
		print = ft_specifier_s(args, lst);
	if (*s == '%')
		print = ft_specifier_prcntge(lst);
	if (*s == 'X' || *s == 'x')
		print = ft_specifier_Xx(args, lst);
	if (*s == 'p')
		print = ft_specifier_p(args, lst);
	return (print);
}

int	ft_prscion(const char *s, t_lst *lst, va_list args)
{
	int	i;

	i = 0;
	if (s[i] == '.')
	{
		i++;
		if (s[i] == '*')
			lst->precision = va_arg(args, int);
		else
			lst->precision = atoi(&s[i]);
		i += ft_countlen(&s[i]);
	}
	if (lst->precision < -1)
		lst->precision = -1;
	return (i);
}

int	ft_width(const char *s, t_lst *lst, va_list args)
{
	int	i;

	i = 0;
	while (s[i] == '-' || s[i] == '0')
		i++;
	if (s[i] == '*')
	{
		lst->width = va_arg(args, int);
		if (lst->width < 0)
		{
			lst->width = lst->width * -1;
			lst->dash = 1;
		}
	}
	else
		lst->width = ft_atoi(s + i);
	i += ft_countlen(&s[i]);
	return (i);
}

int	ft_dashzero(const char *s, t_lst *lst)
{
	if (s[0] == '-')
	{
		lst->dash = 1;
		if (s[1] == '0')
		{
			lst->zero = 1;
			return (2);
		}
		return (1);
	}
	if (s[0] == '0')
	{
		lst->zero = 1;
		if (s[1] == '-')
		{
			lst->dash = 1;
			return (2);
		}
		return (1);
	}
	return (0);
}

int	ft_filler(const char *s, t_lst *lst, va_list args)
{
	int	i;

	i = 0;
	i = ft_dashzero(s + i, lst);
	i += ft_width(s + i, lst, args);
	i += ft_prscion(s + i, lst, args);
	lst->specifier[0] = s[i];
	if (lst->dash == 1 && lst->zero == 1)
		lst->zero = 0;
	if ((s[i] == 'i' || s[i] == 'u' || s[i] == 'd') && lst->precision > -1)
		lst->zero = 0;
	return (i);
}
