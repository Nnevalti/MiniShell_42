NAME		=	Minishell

# COMPILER
CC			=	gcc

# FLAGS
$(CFLAGS)	:
				-Wall -Werror -Wextra

# HEADER
INC_DIR		=	./include
INC			=	-I $(INC_DIR)

# SOURCES
SRC_DIR		=	./srcs
SRC			=	main.c \
				builtins.c \
				env.c \
				utils.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
				ft_split_command_line.c

# OBJETS
OBJS_NAME	=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(SRC_DIR)/, $(OBJS_NAME))


# FT_PRINTF
PRINT_DIR	=	$(addprefix $(SRC_DIR)/, ft_printf)
PRINT_INC	=	-I $(PRINT_DIR)
PRINT_LNK	=	-L $(PRINT_DIR) -lftprintf
PRINTF		=	$(addprefix $(PRINT_DIR)/, libftprintf.a)

# LIBFT LIB
FT_DIR		=	$(addprefix $(SRC_DIR)/, libft)
FT_INC		=	-I $(FT_DIR)
FT_LNK		=	-L $(FT_DIR) -lft
LIBFT		=	$(addprefix $(FT_DIR), libft.a)

GNL_DIR		=	$(addprefix $(SRC_DIR)/, get_next_line)
GNL_INC		=	-I $(GNL_DIR)

# RULES
all			:	$(LIBFT) $(PRINTF) $(NAME)

$(LIBFT)	:
				@echo "\nCompiling $(FT_DIR)..."
				@make -C $(FT_DIR)

$(PRINTF)	:
				@echo "\nCompiling $(PRINT_DIR)..."
				@make -C $(PRINT_DIR)

$(NAME)		:
				$(CC) $(CFLAGS) $(FT_INC) $(PRINT_INC) $(GNL_INC) $(INC) \
				$(addprefix $(SRC_DIR)/, $(SRC)) $(FT_LNK) $(PRINT_LNK) -o $(NAME)

clean		:
				@rm -rf $(OBJS)
				make clean -C $(FT_DIR)
				make clean -C $(PRINT_DIR)

fclean		:	clean
				@echo "\nCleaning Directories..."
				rm -f $(NAME)
				make fclean -C $(FT_DIR)
				make fclean -C $(PRINT_DIR)

re			:	fclean all

run			:	re
				./Minishell
