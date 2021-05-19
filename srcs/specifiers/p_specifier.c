#include "../../ft_printf.h"

int	ft_specifier_p(va_list args, t_lst *lst)
{
	unsigned long arg;
	char *str;
	char *chrestic;

	chrestic = ft_calloc(3, sizeof(char));
	if (!chrestic)
		return (0);
	chrestic[0] = '0';
	chrestic[1] = 'x';

	arg = va_arg(args, unsigned long);
	str = ft_hexitoa(arg ,'a');
	if (str[0] == '0' && str[1] == '\0')
	{
			str[0] = '\0';
			arg = 1;
	}
	//ft_printf("\nstr = %s\n", str);
	str = ft_fstrjoin(chrestic, str, 0);
	//str = ft_inclprcsion_Xx(str, ft_strlen(str), lst->precision);
	//printf("\nstr = %s\n", str);
	ft_inclwidth_u(str, arg, lst);
	//free(str);
	return (1);
}