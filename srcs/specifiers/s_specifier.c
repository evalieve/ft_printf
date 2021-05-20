 #include "../../ft_printf.h"

int	ft_inclwidth_s(char *str, t_lst *lst, int strlen)
{
	int wlen;

	wlen = lst->width - strlen;
	if (wlen < 0)
		wlen = 0;
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
	return (wlen);
}

char	*ft_inclprcsion_s(char *str, int arglen, int prlen)
{
	char	*dup;

	str = ft_strdup(str);
	if (prlen < arglen && prlen != -1)
	{
		dup = ft_calloc(prlen + 1, sizeof(char));
		if (!dup)
			return (0);
		ft_strlcpy(dup, str, prlen + 1);
		free(str);
		return (dup);
	}
	return (str);
}

int	ft_specifier_s(va_list args, t_lst *lst)
{
	char *str;
	int arglen;
	int len;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	arglen = ft_strlen(str);
	str = ft_inclprcsion_s(str, arglen, lst->precision);
	arglen = ft_strlen(str);
	len = ft_inclwidth_s(str, lst, arglen);
    free(str);
	return (arglen + len);
}