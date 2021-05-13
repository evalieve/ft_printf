#include <stdio.h>
#include "ft_printf.h"
#include "libft.h"

char	*ft_fstrjoin(char *s1, char *s2, int i)
{
	char	*s3;

	if (!s1 || !s2)
		return (0);
	s3 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s3)
		return (0);
	ft_memcpy(s3, s1, ft_strlen(s1));
	ft_strlcpy(&s3[ft_strlen(s1)], &s2[i], ft_strlen(s2 + i) + 1);
	free(s1);
	free(s2);
	return (s3);
}


int	ft_countlen(const char *s)
{
	int i;

	i = 0;
	if (s[i] == '-' || s[i] == '*')
		i++;
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

void	ft_inclwidth(char *str, int width, int dash, int zero, int precision, int c)
{
	int len;

	len = width - ft_countlen(str);	
	if (precision == 0 && c == 0)
	{
		str[0] = '\0';
		len++;
	}
	if (dash == 1)
	{
		ft_putstr_fd(str, 1);
		while (len > 0)				// functie voor putchar
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

char	*ft_inclprcsion(char *c, int prlen, int neg)
{
	int arglen;
	char *zeros;
	char *str;
	
	if (c[0] == '-')
		neg++;
	arglen = ft_countlen(&c[neg]);
	if (prlen > arglen)
	{
		zeros = ft_calloc(prlen - arglen + 1, sizeof(char));
		if (!zeros)
			return (0);
		zeros[0] = '-';
		while (prlen - arglen > 0)
		{
			prlen--;
			zeros[prlen - arglen + neg] = '0';
		}
		str = ft_fstrjoin(zeros, c, neg);
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
	int neg;

	neg = 0;
	chr = va_arg(args, int);
	c = ft_itoa(chr);
	if (!c)
			return (0);
	str = ft_inclprcsion(c, lst->precision, neg);
	if (lst->precision > -1)
		lst->zero = 0;
	ft_inclwidth(str, lst->width, lst->dash, lst->zero, lst->precision, chr);
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

int	ft_prscion(const char *s, t_lst *lst, va_list args)
{
	int i;

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
								//printf("p = %d\n", lst->precision);
	return (i);
}

int	ft_width(const char *s, t_lst *lst, va_list args)
{
	int i;

	i = 0;
								//printf("s = %s\n", s);
	if (s[i] == '*')
	{
		lst->width = va_arg(args, int);	
		//printf("i\n");
	}
	else if (ft_isdigit(s[i]))
		lst->width = ft_atoi(s);
								//printf("width in function %d\n", ft_atoi(s));
								//printf("w = %d\n", lst->width);
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

int	ft_filler(const char *s, t_lst *lst, va_list args)
{
	int i;

	i = 0;
								//printf("\n%s\n", s);
	i = ft_dashzero(s + i, lst);
								//printf("i = %d\n", i);
	i += ft_width(s + i, lst, args);
								//printf("ii = %d\n", i);
	i += ft_prscion(s + i, lst, args);
								//printf("iii = %d\n", i);
	lst->specifier[0] = s[i];
	if (lst->dash == 1 && lst->zero == 1)
		lst->zero = 0;
								// printf("\n\ndash %d\n", lst->dash);
								// printf("zero %d\n", lst->zero);
								// printf("width %d\n", lst->width);
								 //printf("precision %d\n", lst->precision);
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
			ret += ft_filler(s + ret, &lst, args);
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
	// ft_printf("1 :\n%d=%7d=%.7d=%.d=%010.d=%0.7d\n", 999, 999, 12345, 12345, 12345, 12345);
	// printf("%d=%7d=%.7d=%.d=%010.d=%0.7d\n\n", 999, 999, 12345, 12345, 12345, 12345);
	// ft_printf("2 :\n%7.5d=%7.2d=%4.3d=%3.4d=%6.7d=%2.7d\n", 123, 123, 12345, 12345, 12345, 12345);
	// printf("%7.5d=%7.2d=%4.3d=%3.4d=%6.7d=%2.7d\n\n", 123, 123, 12345, 12345, 12345, 12345);
	// ft_printf("3 :\n%-7.5d=%-7.2d=%-4.3d=%-3.4d=%-6.7d=%-2.7d\n", 123, 123, 12345, 12345, 12345, 12345);
	// printf("%-7.5d=%-7.2d=%-4.3d=%-3.4d=%-6.7d=%-2.7d\n\n", 123, 123, 12345, 12345, 12345, 12345);
	// ft_printf("4 :\n%07.5d=%07.2d=%04.3d=%03.4d=%06.7d=%02.7d\n", 123, 123, 12345, 12345, 12345, 12345);
	// printf("%07.5d=%07.2d=%04.3d=%03.4d=%06.7d=%02.7d\n\n", 123, 123, 12345, 12345, 12345, 12345);
	// ft_printf("5 (negative numbers) :\n%7.5d=%7.2d=%4.3d=%3.4d=%7.9d=%2.9d\n", -123, 123, -12345, -12345, -12345, -12345);
	// printf("%7.5d=%7.2d=%4.3d=%3.4d=%7.9d=%2.9d\n\n", -123, 123, -12345, -12345, -12345, -12345);
	// ft_printf("6 (negative numbers) :\n%-7.5d=%-7.2d=%-4.3d=%-3.4d=%-7.9d=%-2.9d\n", -123, 123, -12345, -12345, -12345, -12345);
	// printf("%-7.5d=%-7.2d=%-4.3d=%-3.4d=%-7.9d=%-2.9d\n\n", -123, 123, -12345, -12345, -12345, -12345);
	// ft_printf("7 (negative numbers) :\n%07.5d=%07.2d=%04.3d=%03.4d=%07.9d=%02.9d\n", -123, 123, -12345, -12345, -12345, -12345);
	// printf("%07.5d=%07.2d=%04.3d=%03.4d=%07.9d=%02.9d\n\n", -123, 123, -12345, -12345, -12345, -12345);
	// ft_printf("8 :\n%7.7d=%2.2d=%4.3d=%3.4d=%2.2d\n", 123, 123, 1234, 1234, 12);
	// printf("%7.7d=%2.2d=%4.3d=%3.4d=%2.2d\n\n", 123, 123, 1234, 1234, 12);
	// ft_printf("9 :\n%7.7d=%2.2d=%5.3d=%3.5d=%3.3d\n", -123, -123, -1234, -1234, -12);
	// printf("%7.7d=%2.2d=%5.3d=%3.5d=%3.3d\n\n", -123, -123, -1234, -1234, -12);
	// ft_printf("10 :\n%-7.7d=%-2.2d=%-4.3d=%-3.4d=%-2.2d\n", 123, 123, 1234, 1234, 12);
	// printf("%-7.7d=%-2.2d=%-4.3d=%-3.4d=%-2.2d\n\n", 123, 123, 1234, 1234, 12);
	// ft_printf("11 :\n%-7.7d=%-2.2d=%-5.3d=%-3.5d=%-3.3d\n", -123, -123, -1234, -1234, -12);
	// printf("%-7.7d=%-2.2d=%-5.3d=%-3.5d=%-3.3d\n\n", -123, -123, -1234, -1234, -12);
	// ft_printf("12 :\n%07.7d=%02.2d=%04.3d=%03.4d=%02.2d\n", 123, 123, 1234, 1234, 12);
	// printf("%07.7d=%02.2d=%04.3d=%03.4d=%02.2d\n\n", 123, 123, 1234, 1234, 12);
	// ft_printf("13 :\n%-7.7d=%-2.2d=%-5.3d=%-3.5d=%-3.3d\n", -123, -123, -1234, -1234, -12);
	// printf("%07.7d=%02.2d=%05.3d=%03.5d=%03.3d\n\n", -123, -123, -1234, -1234, -12);
	ft_printf("14 :\n%0.5d=%7.0d=%0.3d=%3.0d=%0.5d=%7.0d=%0.3d=%3.0d=%6.0d=%6.d=%0.7d=%0.0d=%0.d\n", 123, 123, 12345, 12345, -123, -123, -12345, -12345, 0, 0, 0, 0, 0);
	printf("%0.5d=%7.0d=%0.3d=%3.0d=%0.5d=%7.0d=%0.3d=%3.0d=%6.0d=%6.d=%0.7d=%0.0d=%0.d\n\n", 123, 123, 12345, 12345, -123, -123, -12345, -12345, 0, 0, 0, 0, 0);
	// ft_printf("15 :\n%15.5d=%15.15d=%15.5d=%15.15d\n", 2147483647, 2147483647, -2147483647, -2147483647);
	// printf("%15.5d=%15.15d=%15.5d=%15.15d\n\n", 2147483647, 2147483647, -2147483647, -2147483647);
	// ft_printf("16 :\n%-15.5d=%-15.15d=%-15.5d=%-15.15d\n", 2147483647, 2147483647, -2147483647, -2147483647);
	// printf("%-15.5d=%-15.15d=%-15.5d=%-15.15d\n\n", 2147483647, 2147483647, -2147483647, -2147483647);
	// ft_printf("17 :\n%015.5d=%015.15d=%015.5d=%015.15d\n", 2147483647, 2147483647, -2147483647, -2147483647);
	// printf("%015.5d=%015.15d=%015.5d=%015.15d\n\n", 2147483647, 2147483647, -2147483647, -2147483647);
	ft_printf("18 :\n%d=%d=%15.5d=%15.15d\n", 001, -001, 001, -001);
	printf("%d=%d=%15.5d=%15.15d\n\n", 001, -001, 001, -001);
	ft_printf("19 :\n%-d=%-d=%-15.5d=%-15.15d\n", 001, -001, 001, -001);
	printf("%-d=%-d=%-15.5d=%-15.15d\n\n", 001, -001, 001, -001);
	ft_printf("20 :\n%0d=%0d=%015.5d=%015.15d\n", 001, -001, 001, -001);
	printf("%0d=%0d=%015.5d=%015.15d\n\n", 001, -001, 001, -001);
	// ft_printf("21 :\n%07.5d=%d=%-d=%-d=%0d=%0d\n", +123, +0, +123, +0, +123, +0);
	//  printf("%07.5d=%d=%-d=%-d=%0d=%0d\n\n", +123, +0, +123, +0, +123, +0);
	// ft_printf("%*.*d\n", 4, 7, 123);
	// printf("%*.*d\n", 4, 7, 123);
	// ft_printf("%4.d\n", 0);
	// printf("%4.d\n", 0);
	ft_printf("14 :\n%6.0d=%6.d=%8d=%8.0d=%0.7d=%0.0d=%0.d\n", 0, 0, 0, 0, 0, 0, 0);
	printf("%6.0d=%6.d=%8d=%8.0d=%0.7d=%0.0d=%0.d\n\n", 0, 0, 0, 0, 0, 0, 0);
	return (0);
}