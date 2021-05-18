#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_lst
{
	int zero;
	int dash;
	int width;
	int precision;
	char specifier[2];
}					t_lst;

int	ft_printf(const char *s, ...);

void	ft_init(t_lst *lst);

int	ft_filler(const char *s, t_lst *lst, va_list args);

void	ft_checker(const char *s, va_list args, t_lst *lst);

int	ft_countlen(const char *s);

int	ft_specifier_di(va_list args, t_lst *lst);

void	ft_specifier_c(va_list args, t_lst *lst);

char	*ft_fstrjoin(char *s1, char *s2, int i);

void	ft_putchar(char c, int amount);

char	*ft_unsitoa(unsigned int nbr);

int	ft_specifier_u(va_list args, t_lst *lst);

int	ft_specifier_prcntge(t_lst *lst);

int	ft_specifier_s(va_list args, t_lst *lst);

int	ft_specifier_Xx(va_list args, t_lst *lst);

void	ft_inclwidth_u(char *str, int arg, t_lst *lst);
char	*ft_inclprcsion_di(char *nbr, int prlen, int neg);

#endif