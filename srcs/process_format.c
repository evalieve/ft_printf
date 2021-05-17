#include "../ft_printf.h"

void	ft_checker(const char *s, va_list args, t_lst *lst)
{
	if (*s == 'd' || *s == 'i')
		ft_specifier_di(args, lst);
	if (*s == 'c')
		ft_specifier_c(args, lst);
	if (*s == 'u')
	 	ft_specifier_u(args, lst);
	if (*s == 's')
		ft_specifier_s(args, lst);
	if (*s == '%')
		ft_specifier_prcntge(lst);
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
	return (i);
}

int	ft_width(const char *s, t_lst *lst, va_list args)
{
	int	i;

	i = 0;
	if (s[i] == '*')
		lst->width = va_arg(args, int);
	else if (ft_isdigit(s[i]))
		lst->width = ft_atoi(s);
	i = ft_countlen(&s[i]);
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
	return (i);
}
