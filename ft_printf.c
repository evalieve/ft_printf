#include <stdio.h>
#include "ft_printf.h"
#include "libft.h"

char	*ft_fstrjoin(char *s1, char *s2)
{
	char	*s3;

	if (!s1 || !s2)
		return (0);
	s3 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s3)
		return (0);
	ft_memcpy(s3, s1, ft_strlen(s1));
	ft_strlcpy(&s3[ft_strlen(s1)], s2, ft_strlen(s2) + 1);
	free(s1);
	free(s2);
	return (s3);
}


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

void	ft_inclwidth(char *str, int width, int dash, int zero)
{
	int len;

	len = width - ft_countlen(str);	
	if (dash == 1)
	{
		ft_putstr_fd(str, 1);
		while (len > 0)
		{
			ft_putchar_fd(' ', 1);
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			if (zero == 1)
				ft_putchar_fd('0', 1);
			else
				ft_putchar_fd(' ', 1);
			len--;
		}
		ft_putstr_fd(str,1);
	}
	free(str);
}

char	*ft_inclprcsion(char *c, int prlen)
{
	int arglen;
	char *zeros;
	char *str;

	arglen = ft_countlen(c);
	if (prlen > arglen)
	{
		zeros = ft_calloc(prlen - arglen + 1, sizeof(char));
		if (!zeros)
			return (0);
		while (prlen - arglen > 0)
		{
			prlen--;
			zeros[prlen - arglen] = '0';
		}
		str = ft_fstrjoin(zeros, c);
		if (!str)
			return (0);
		return (str);
	}
	return (c);
}

int	ft_specifier_di(va_list args, t_lst *lst)
{
	char *str;
	char *c;
	int chr;

	chr = va_arg(args, int);
	// if (chr < 0)
	// {
	// 	ft_putchar_fd('-', 1);
	// 	chr = chr * -1;
	// }
	c = ft_itoa(chr);
	if (!c)
			return (0);
	str = ft_inclprcsion(c, lst->precision);
	if (lst->precision > -1)
		lst->zero = 0;
	ft_inclwidth(str, lst->width, lst->dash, lst->zero);
	return (1);
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
								//printf("%d\n", lst->precision);
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
	l = -123;
	ft_printf("hallo %0.8i %-04.d %-2d %7.5d dudes\n", i, j, k, l);
								//printf("\nl = %d\n", l);
								printf("hallo %0.8i %-4.d %-2d %7.5d dudes\n", i, j, k, l);
	return (0);
}