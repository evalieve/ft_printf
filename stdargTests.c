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
	return ;
}

void	ft_specifier_c(va_list args)
{
	int ar;

	ar = va_arg(args, int);
	ft_putchar_fd(ar, 1);
	return ;
}

void	ft_specifier_di(va_list args)
{
	int ar;
	char *c;

	ar  = va_arg(args, int);
	c = ft_itoa(ar);
	ft_putstr_fd(c, 1);
	return ;
}

int	ft_checker(const char *s, int count, va_list args)
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
	return (count + 2);
}

void	ft_init(t_lst *lst)
{
	lst->zero = 0;
	lst->dash = 0;
	lst->width = -1;
	lst->precision = -1;
	lst->specifier[0] = '\0';
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
		if (s[ret] != '%')
		{
			write(1, &s[ret], 1);
			ret++;
		}
		else
			ret += ft_checker(&s[ret + 1], ret, args);
	}
	return (ret);
}

int	main(void)
{
	int i, j, k, l;
	int *iptr;

	i = 10;
	j = 20;
	k = 30;
	iptr = &i;
	l = ft_printf("chars printed: %d, %d and %d and a char: %c, and again another string: %s and for the lols %%. And also a pointer: %p = ", i, j, k, 'k', "Hello World!", iptr);
	printf("%d\n", l);
	int b=0xFAFA;
	
	printf("value of a: %X [%x]\n", 0x1f, 0x1f);
	printf("value of b: %X [%x]\n",b,b);
	return (0);
}