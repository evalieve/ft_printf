#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_lst
{
	int zero;
	int dash;
	int width;
	int precision;
	char specifier[2];
}					t_lst;

#endif