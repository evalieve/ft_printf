#include "../../ft_printf.h"

char	*ft_inclprcsion_s(char *str, int arglen, int prlen)
{
	char	*dup;

	if (prlen < arglen)
	{
		dup = ft_calloc(prlen + 1, sizeof(char));
		ft_strlcpy(dup, str, prlen + 1);
		return (dup);
	}
	return (str);
}

int	ft_specifier_s(va_list args, t_lst *lst)
{
	char *str;
	int arglen;

	str = va_arg(args, char *);
	arglen = ft_strlen(str);
	printf("arglen = %d\n", arglen);
	str = ft_inclprcsion_s(str, arglen, lst->precision);
	ft_putstr_fd(str, 1);
	return (1);
}