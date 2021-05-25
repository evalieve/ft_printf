#include "ft_printf.h"

int	ft_prcssformat()
{
	// shorten printf function bc too many lines
}

int	ft_printf(const char *s, ...)
{
	int		track;
	int		ret;
	int		check;
	va_list	args;
	t_lst	lst;

	track = 0;
	ret = 0;
	va_start(args, s);
	while (s[track])
	{
		if (s[track] == '%')
		{
			track++;
			ft_init(&lst);
			track += ft_filler(s + track, &lst, args);
			check = ft_checker(s + track, args, &lst);
			if (check == -1)
				return (-1);
			else
				ret += check;
		}
		else
		{
			write(1, s + track, 1);
			ret++;
		}
		track++;
	}
	return (ret);
}
