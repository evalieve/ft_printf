NAME = libftprintf.a

LIBFT = libft.a

HEADER = ft_printf.h

SRCS = ft_printf.c srcs/specifiers/c_specifier.c srcs/specifiers/di_specifier.c srcs/specifiers/s_specifier.c srcs/specifiers/u_specifier.c srcs/specifiers/prcntge_specifier.c srcs/process_format.c srcs/utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	cp libft/$< $@
	ar rc $@ $(OBJS)

$(LIBFT) :
	make -C libft/

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)
	make fclean -C libft/

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
