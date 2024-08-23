# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/10 10:25:31 by hel-bouk          #+#    #+#              #
#    Updated: 2024/08/18 17:24:54 by hel-bouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=libft.a
CC := gcc
CFLAGS := -Wall -Wextra -Werror
RM := rm -f
head := libft.h
SRC :=	ft_memset.c ft_isalpha.c ft_strjoin.c  ft_strmapi.c ft_isprint.c \
	ft_striteri.c ft_memmove.c ft_bzero.c ft_strlen.c smart_split.c \
	ft_memcmp.c ft_putendl_fd.c ft_itoa.c ft_memchr.c  hexa_to_int.c \
	ft_isascii.c ft_strdup.c ft_memcpy.c ft_putnbr_fd.c \
	ft_strlcpy.c ft_split.c ft_putchar_fd.c ft_substr.c \
	ft_strnstr.c ft_atoi.c ft_isalnum.c ft_putstr_fd.c \
	ft_calloc.c ft_isdigit.c ft_strncmp.c ft_toupper.c ft_strtrim.c \
	ft_strrchr.c ft_strlcat.c ft_tolower.c ft_strchr.c
OBJS := $(SRC:.c=.o)
BONUS := ft_lstnew_bonus.c ft_lstdelone_bonus.c ft_lstsize_bonus.c ft_lstiter_bonus.c  ft_lstclear_bonus.c \
	 ft_lstmap_bonus.c ft_lstadd_front_bonus.c ft_lstadd_back_bonus.c ft_lstlast_bonus.c
BONUS_OBJS := $(BONUS:.c=.o)
all : $(NAME)
$(NAME) : $(OBJS)
	@ar rc $(NAME) $(OBJS)
bonus : $(BONUS_OBJS)
	@ar rc $(NAME) $(BONUS_OBJS)
%.o : %.c $(head)
	@$(CC) $(CFLAGS) -c $< -o $@
clean :
	@$(RM) $(OBJS) $(BONUS_OBJS)
fclean : clean
	@$(RM) $(NAME)
re : fclean all

.PHONY : all bonus clean fclean re
