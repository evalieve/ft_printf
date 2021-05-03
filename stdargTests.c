#include <stdio.h>
#include "ft_printf.h"
#include "libft.h"

// void	ft_specifier_p(va_list args)
// {
// 	char *ar;

// 	ar = va_arg(args, void *);
// 	ft_putstr_fd(ar, 1);
// 	return ;
// }

void	ft_specifier_s(va_list args)
{
	char *ar;

	ar = va_arg(args, char *);
	ft_putstr_fd(ar, 1);
}

void	ft_specifier_c(va_list args)
{
	int ar;

	ar = va_arg(args, int);
	ft_putchar_fd(ar, 1);
}

void	ft_specifier_di(va_list args)
{
	int ar;
	char *c;

	ar  = va_arg(args, int);
	c = ft_itoa(ar);
	ft_putstr_fd(c, 1);
}

void	ft_checker(const char *s, va_list args)
{
	if (*s == 'd' || *s == 'i')
		ft_specifier_di(args);
	if (*s == 'c')
		ft_specifier_c(args);
	if (*s == 's')
		ft_specifier_s(args);
	// if (*s == 'p')
	// 	ft_specifier_p(args);
	if (*s == '%')
		ft_putchar_fd('%', 1); // flags etc
}

int	ft_countlen(const char *s)
{
	int i;

	i = 0;
	while (ft_isdigit(s[i]))
		i++;
	return (i);
}

int	ft_prscion(const char *s, t_lst *lst)
{
	int i;

	i = 0;
	if (s[i] == '.')
	{
		i++;
		lst->precision = atoi(&s[i]);
		i = ft_countlen(&s[i]);
	}
	return (i + 1);
}

int	ft_width(const char *s, t_lst *lst)
{
	int i;

	i = 0;
	printf("s = %s\n", s);
	if (ft_isdigit(s[i]))
	{
		lst->width = ft_atoi(s);
		printf("lol\n");
	}
	printf("width in function %d\n", ft_atoi(s));
	i = ft_countlen(&s[i]);
	return (i);
}

int	ft_dashzero(const char *s, t_lst *lst)
{
	int i;
	int flag;
	
	i = 0;
	flag = 0;
	while(s[i] == '0' || s[i] == '-')
	{
		if (s[i] == '-')
			lst->dash = 1;
		if (s[i] == '0' && lst->zero == 0)
		{
			lst->zero = 1;
			flag = 1;
		}
		i++;
	}
	return (i);
}

int	ft_filler(const char *s, t_lst *lst)
{
	int i;

	i = 0;
	//printf("\n%s\n", s);
	i = ft_dashzero(s + i, lst);
	printf("\ndash %d\n", lst->dash);
	printf("zero %d\n", lst->zero);
	i += ft_width(s + i, lst);
	printf("width %d\n", lst->width);
	i += ft_prscion(s + i, lst);
	printf("precision %d\n", lst->precision);
	lst->specifier[0] = s[i];
	printf("specifier %s\n", lst->specifier);
	printf("i = %d\n", i);
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
	ft_init(&lst);
	va_start(args, s);
	while (s[ret])
	{
		if (s[ret] == '%')
		{
			ret += ft_filler(s + ret + 1, &lst);
			ft_checker(s + ret + 1, args);
		}
		else
		{
			write(1, s + ret, 1);
			ret++;
		}
		//printf("\nret = %d\n", ret);
			//printf("dash= %d\n", lst.dash);
	}
	return (ret);
}

int	main(void)
{
	int i, j, k, l;

	i = 10;
	j = 20;
	k = 30;
	l = ft_printf("hallo %-00.4d", i);
	printf("\nl = %d\n", l);
	return (0);
}