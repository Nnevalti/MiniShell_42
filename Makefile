NAME		=	Minishell

# COMPILER
CC			=	gcc

# FLAGS
$(CFLAGS)	:	-Wall -Werror -Wextra

# HEADER
INC			=	-I ./include

# SOURCES
SRC_DIR		=	./srcs
SRC			=	main.c \
				builtins.c \
				env.c \
				pipe.c \
				utils.c \
				free.c \
				ft_split_command_line.c

# OBJETS
OBJS_NAME	=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(SRC_DIR)/, $(OBJS_NAME))

# LIBFT LIB
FT_DIR		=	./libft
FT_INC		=	-I $(FT_DIR)
FT_LNK		=	-L $(FT_DIR) -lft
LIBFT		=	$(addprefix $(FT_DIR)/, libft.a)

# RULES
all			:	$(LIBFT) $(NAME)

$(LIBFT)	:
				@echo "\nCompiling $(FT_DIR)..."
				@make -C $(FT_DIR)

$(NAME)		:
				$(CC) $(CFLAGS) $(INC) \
				$(addprefix $(SRC_DIR)/, $(SRC)) $(LIBFT) -o $(NAME)

clean		:
				@rm -rf $(OBJS)
				make clean -C $(FT_DIR)

fclean		:	clean
				@echo "\nCleaning Directories..."
				rm -f $(NAME)
				make fclean -C $(FT_DIR)

re			:	fclean all

run			:	re
				./Minishell
