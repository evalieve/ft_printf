#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	int track;
	int ret;
	va_list args;
	t_lst lst;

	track = 0;
	ret = 0;
	va_start(args, s);
	//printf("\nstarttttt\n");
	while (s[track])
	{
		if (s[track] == '%')
		{
			track++;
			ft_init(&lst);
			track += ft_filler(s + track, &lst, args);
			ret += ft_checker(s + track, args, &lst);
		}
		else
		{
			write(1, s + track, 1);
			ret++;
		}
		track++;
		//printf("\nret in function = %d\n", ret);
	}
	return (ret);
}
