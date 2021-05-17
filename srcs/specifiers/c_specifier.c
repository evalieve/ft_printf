#include "../../ft_printf.h"

void	ft_specifier_c(va_list args, t_lst *lst)
{
	int	ar;
	int	lenwidth;

	lenwidth = lst->width - 1;
	ar = va_arg(args, int);
	if (lst->dash == 1)
		ft_putchar_fd(ar, 1);
	if (lenwidth > 0)
		ft_putchar(' ', lenwidth);
	if (lst->dash == 0)
		ft_putchar_fd(ar, 1);
}