#include "../../ft_printf.h"

int	ft_specifier_prcntge(t_lst *lst)
{
	int	lenwidth;

	lenwidth = lst->width - 1;
	if (lenwidth < 0)
		lenwidth = 0;
	if (lst->dash == 1)
		ft_putchar_fd('%', 1);
	if (lenwidth > 0)
	{
		if (lst->zero == 1)
			ft_putchar('0', lenwidth);
		else
			ft_putchar(' ', lenwidth);
	}
	if (lst->dash == 0)
		ft_putchar_fd('%', 1);
	return (lenwidth + 1);
}