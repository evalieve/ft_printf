#include "../../ft_printf.h"

// void	ft_inclwidth_Xx(char *str, unsigned int arg, t_lst *lst)
// {
// 	int	len;

// 	len = lst->width - ft_strlen(str);
// 	//printf("\nstr= %s\n", str);
// 	if (lst->precision == 0 && arg == 0)
// 	{
// 		str[0] = '\0';
// 		if (lst->width > 0)
// 			len++;
// 		//printf("3\n");
// 	}
// 	if (lst->dash == 1)
// 	{
// 		ft_putstr_fd(str, 1);
// 		ft_putchar(' ', len);
// 	//	printf("4\n");
// 	}
// 	else
// 	{
// 		if (lst->zero == 1 && lst->precision == -1)
// 			ft_putchar('0', len);
// 		else
// 			ft_putchar(' ', len);
// 		ft_putstr_fd(str, 1);
// 	//	printf("5\n");
// 	}
// 	free(str);
// }

char	*ft_inclprcsion_Xx(char *str, int strlen, int prlen)
{
	char *new;

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
		if (!str)
			return (0);
		return (new);
	}
	return (str);
}

char	*ft_hexitoa(unsigned int num, char type)
{
	int len;
	unsigned int numdup;
	char *str;

	len = 0;
	numdup = num;
	if (numdup == 0)
		len++;
	while (numdup)
	{
		numdup = numdup / 16;
		len++;
	}
	//printf("len = %d\n", len);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	//str[len] = '\0';
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
	unsigned int arg;
	char *str;
	char type;
	int strlen;

	type = 'a';
	if (*lst->specifier == 'X')
		type = 'A';
	arg = va_arg(args, unsigned int);
	str = ft_hexitoa(arg, type);
	strlen = ft_strlen(str);
	str = ft_inclprcsion_Xx(str, strlen, lst->precision);
	//ft_inclwidth_Xx(str, arg, lst);
	ft_inclwidth_u(str, arg, lst);
	return (1);
}