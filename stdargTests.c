#include <stdio.h>
#include "ft_printf.h"
#include "libft.h"

int	ft_countlen(const char *s)
{
	int i;

	i = 0;
	while (ft_isdigit(s[i]))
		i++;
	return (i);
}

void	ft_specifier_s(va_list args)
{
	char *ar;

	ar = va_arg(args, char *);
	ft_putstr_fd(ar, 1);
}

void	ft_specifier_c(va_list args, t_lst *lst)
{
	int ar;
	int i;
	int lenwidth;

	i = 1;
	lenwidth = lst->width;
	ar = va_arg(args, int);
	if (lst->dash == 1)	
		ft_putchar_fd(ar, 1);
	if (lenwidth > 0)
	{
		while (i < lenwidth)
		{
			ft_putchar_fd(' ',1);
			i++;
		}
	}
	if (lst->dash == 0)
		ft_putchar_fd(ar, 1);
}

void	ft_specifier_di(va_list args, t_lst *lst)
{
	int ar;
	char *str;
	char *c;
	int arglen;
	int prlen;

	prlen = lst->precision;
	ar  = va_arg(args, int);
	c = ft_itoa(ar);
	arglen = ft_countlen(ar);
	if (prlen > arglen)
	{
		str = (char *)malloc(prlen + 1 * sizeof(char));
		if (!str)
			//return (0);
		str[prlen] = '\0';
	}
	ft_putstr_fd(str, 1);
}

void	ft_checker(const char *s, va_list args, t_lst *lst)
{
	if (*s == 'd' || *s == 'i')
		ft_specifier_di(args, lst);
	if (*s == 'c')
		ft_specifier_c(args, lst);
	if (*s == 's')
		ft_specifier_s(args);
	if (*s == '%')
		ft_putchar_fd('%', 1);
}

int	ft_prscion(const char *s, t_lst *lst)
{
	int i;

	i = 0;
	if (s[i] == '.')
	{
		i++;
		lst->precision = atoi(&s[i]);
		i += ft_countlen(&s[i]);
	}
	return (i);
}

int	ft_width(const char *s, t_lst *lst)
{
	int i;

	i = 0;
								//printf("s = %s\n", s);
	if (ft_isdigit(s[i]))
		lst->width = ft_atoi(s);
								//printf("width in function %d\n", ft_atoi(s));
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
	if (s[0] ==  '0')
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

int	ft_filler(const char *s, t_lst *lst)
{
	int i;

	i = 0;
								//printf("\n%s\n", s);
	i = ft_dashzero(s + i, lst);
								//printf("i = %d\n", i);
	i += ft_width(s + i, lst);
								//printf("ii = %d\n", i);
	i += ft_prscion(s + i, lst);
								//printf("iii = %d\n", i);
	lst->specifier[0] = s[i];
	if (lst->dash == 1 && lst->zero == 1)
		lst->zero = 0;
								// printf("\n\ndash %d\n", lst->dash);
								// printf("zero %d\n", lst->zero);
								// printf("width %d\n", lst->width);
								// printf("precision %d\n", lst->precision);
								// printf("specifier %s\n\n", lst->specifier);
	return (i);
}

void	ft_init(t_lst *lst)
{
	lst->zero = 0;
	lst->dash = 0;
	lst->width = -1;
	lst->precision = -1;
	lst->specifier[0] = '\0';
	lst->specifier[1] = '\0';
}

int	ft_printf(const char *s, ...)
{
	int ret;
	va_list args;
	t_lst lst;

	ret = 0;
	va_start(args, s);
	while (s[ret])
	{
		if (s[ret] == '%')
		{
			ret++;
			ft_init(&lst);
			ret += ft_filler(s + ret, &lst);
			ft_checker(s + ret, args, &lst);
								//printf("ret: %d\n", ret);
		}
		else
			write(1, s + ret, 1);
		ret++;
								//printf("\nret = %d\n", ret);
								//printf("dash= %d\n", lst.dash);
	}
	return (ret);
}

int	main(void)
{
	int i, j, k, l;
	char a, b, c;

	a = 'Y';
	b = 'o';
	c = '!';
	i = 10;
	j = 20;
	k = 30;
	l = ft_printf("hallo %-009.9c %-9c %c dudes\n", a, b, c);
								//printf("\nl = %d\n", l);
								printf("hallo %8.6d %-.1d %7d dudes\n", i, j, k);
	return (0);
}