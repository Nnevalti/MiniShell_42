NAME		=	libftprintf.a

SRCS		=	ft_printf.c \
				ft_flags.c \
				ft_format.c \
				ft_putc.c \
				ft_puts.c \
				ft_utils.c \
				ft_putn.c \
				ft_putu.c \
				ft_putx.c \
				ft_putp.c

DIR			=	srcs/
OBJS		=	$(SRCS:.c=.o)

INCLUDES	=	includes/ft_printf.h

CFLAGS		=	-Wall -Werror -Wextra -I $(INCLUDES)

all			:	$(NAME)

$(NAME)		:
				gcc	-Wall -Werror -Wextra -c $(addprefix $(DIR), $(SRCS))
				ar rc $(NAME) $(OBJS)
				@mkdir -p objs
				@mv $(OBJS) objs

clean		:
				rm -rf $(addprefix objs/, $(OBJS))

fclean		:	clean
				rm -f $(NAME)

re			:	fclean all
