#include "ft_printf.h"

int	ft_stringprcss(int *track, va_list args, t_lst *lst, const char *s)
{
	int	check;

	(*track)++;
	ft_init(lst);
	*track += ft_filler(s + *track, args, lst);
	check = ft_checker(s + *track, args, lst);
	return (check);
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
			check = ft_stringprcss(&track, args, &lst, s);
			if (check == -1)
				return (-1);
			ret += check;
			track++;
			continue ;
		}
		write(1, s + track, 1);
		ret++;
		track++;
	}
	return (ret);
}
