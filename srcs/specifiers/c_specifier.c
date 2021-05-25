#include "../../ft_printf.h"

int	ft_specifier_c(va_list args, t_lst *lst)
{
	int	arg;
	int	lenwidth;

	lenwidth = lst->width - 1;
	arg = va_arg(args, int);
	if (lst->dash == 1)
		ft_putchar_fd(arg, 1);
	if (lenwidth > 0)
		ft_putchar(' ', lenwidth);
	else
		lenwidth = 0;
	if (lst->dash == 0)
		ft_putchar_fd(arg, 1);
	return (lenwidth + 1);
}
