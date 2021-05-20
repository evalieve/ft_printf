#include "../../ft_printf.h"

int	ft_specifier_p(va_list args, t_lst *lst)
{
	unsigned long arg;
	char *str;
	char *chrestic;
	int		len;
	int strlen;

	chrestic = ft_calloc(3, sizeof(char));
	if (!chrestic)
		return (0);
	chrestic[0] = '0';
	chrestic[1] = 'x';

	arg = va_arg(args, unsigned long);
	str = ft_hexitoa(arg ,'a');
	if (lst->precision > -1)
	{
		if (str[0] == '0' && str[1] == '\0')
		{
				str[0] = '\0';
				arg = 1;
		}
	}
	str = ft_fstrjoin(chrestic, str, 0);
	strlen = ft_strlen(str);
	len =  lst->width - strlen;
	if (len < 0)
		len = 0;
	ft_inclwidth_u(str, arg, lst, len);
	return (strlen + len);
}