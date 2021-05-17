#include "ft_printf.h"

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
		}
		else
			write(1, s + ret, 1);
		ret++;
	}
	return (ret);
}
