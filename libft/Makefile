# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: evan-der <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/07 12:28:29 by evan-der      #+#    #+#                  #
#    Updated: 2021/01/14 16:31:23 by evan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER = libft.h

NORMAL = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c \
ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

NORMAL_O = $(NORMAL:.c=.o)

BONUS_O = $(BONUS:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

all : $(NAME)

$(NAME) : $(NORMAL_O)
	ar rc $@ $^

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $<

bonus : $(NORMAL_O) $(BONUS_O)
	ar rc $(NAME) $^

clean :
	$(RM) $(NORMAL_O) $(BONUS_O)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus
