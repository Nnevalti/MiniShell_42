NAME		=	libftprintf.a

SRCS		=	ft_printf.c \
				srcs/ft_flags.c \
				srcs/ft_format.c \
				srcs/ft_putc.c \
				srcs/ft_puts.c \
				srcs/ft_utils.c \
				srcs/ft_putn.c \
				srcs/ft_putu.c \
				srcs/ft_putx.c \
				srcs/ft_putp.c

OBJS		=	$(SRCS:.c=.o)

INCLUDES	=	includes/ft_printf.h

CFLAGS		=	-Wall -Werror -Wextra -I $(INCLUDES)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(INCLUDES) 
				ar rc $(NAME) $(OBJS)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -f $(NAME)

re			:	fclean all
