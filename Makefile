NAME		=	Minishell

# COMPILER
CC			=	gcc

# FLAGS
$(CFLAGS)	:
				-Wall -Werror -Wextra

# HEADER
INC_DIR		=	./include
INC_NAME	=	minishell.h
INC			=	-I $(addprefix $(INC_DIR)/, $INC_NAME)

# SOURCES
SRC_DIR		=	./srcs
SRC			=	main.c \
					builtins.c

# OBJETS
OBJS_NAME	=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(SRC_DIR)/, $(OBJS_NAME))


# FT_PRINTF
PRINT_DIR		=	$(addprefix $(SRC_DIR)/, ft_printf)
PRINT_INC		=	-I $(PRINT_DIR)
PRINT_LNK		=	-L $(PRINT_DIR) -lft
PRINTF		=	$(addprefix $(FT_DIR), ft_printf.a)

# LIBFT LIB
FT_DIR		=	$(addprefix $(SRC_DIR)/, libft)
FT_INC		=	-I $(FT_DIR)
FT_LNK		=	-L $(FT_DIR) -lft
LIBFT		=	$(addprefix $(FT_DIR), libft.a)

# RULES
all			:	$(LIBFT) $(NAME)

$(LIBFT)	:
				@echo "\nCompiling $(FT_DIR)..."
				@make -C $(FT_DIR)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $(INC) $(FT_INC) $(MLX_INC) $(addprefix $(SRC_DIR)/, $(SRC)) $(FT_LNK) $(MLX_LNK) -o $(NAME)

bonus		:	$(OBJS_BNS)
				@echo "\nCompiling $(FT_DIR)..."
				@make -C $(FT_DIR_BNS)
				$(CC) $(CFLAGS) $(INC) $(FT_INC_BNS) $(MLX_INC) $(addprefix $(BNS_DIR)/, $(BNS)) $(FT_LNK_BNS) $(MLX_LNK) -o $(NAME)

clean		:
				@rm -rf $(OBJS)
				@rm -rf $(OBJS_BNS)
				make clean -C $(FT_DIR)
				make clean -C $(FT_DIR_BNS)

fclean		:	clean
				@echo "\nCleaning Directories..."
				rm -f $(NAME)
				rm -f libmlx.dylib
				make fclean -C $(FT_DIR)
				make fclean -C $(FT_DIR_BNS)

re			:	fclean all
