#include "../ft_printf.h"

char	*ft_unsitoa(unsigned int nbr)
{
	int				len;
	unsigned int	cpnbr;
	char			*result;

	len = 0;
	cpnbr = nbr;
	if (cpnbr == 0)
		len++;
	while (cpnbr)
	{
		cpnbr = cpnbr / 10;
		len++;
	}
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (0);
	result[len] = '\0';
	result[0] = '0';
	while (nbr)
	{
		len--;
		result[len] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	return (result);
}

void	ft_putchar(char c, int amount)
{
	if (amount < 1)
		return ;
	while (amount)
	{
		write(1, &c, 1);
		amount--;
	}
}

char	*ft_fstrjoin(char *s1, char *s2, int i)
{
	char	*s3;

	if (!s1 || !s2)
		return (0);
	s3 = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!s3)
		return (0);
	ft_memcpy(s3, s1, ft_strlen(s1));
	ft_strlcpy(&s3[ft_strlen(s1)], &s2[i], ft_strlen(s2 + i) + 1);
	free(s1);
	free(s2);
	return (s3);
}

int	ft_countlen(const char *s)
{
	int i;

	i = 0;
	if (s[i] == '-' || s[i] == '*')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	return (i);
}

void	ft_init(t_lst *lst)
{
	lst->zero = 0;
	lst->dash = 0;
	lst->width = -1;
	lst->precision = -1;
	lst->specifier[0] = '\0';
	lst->specifier[1] = '\0';
}