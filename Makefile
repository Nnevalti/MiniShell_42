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
				builtins2.c \
				builtins3.c \
				env.c \
				utils.c \
				utils2.c \
				free.c \
				ft_lexer.c \
				ft_executor.c \
				ft_parser.c \
				ft_exec.c \
				handle_env.c \
				init.c \
				init_piperedir.c \
				handle_error.c \
				handle_error2.c \
				handle_redir.c \
				handle_pipes.c \
				signal.c \
				opt_tab.c \
				handle_bsq.c \
				prompt.c \
				ft_lexer_utils.c \
				fill_tokens_utils.c \
				ft_parser_utils.c \
				get_new_str_utils.c \
				get_env_array_utils.c \
				handle_error_utils.c \
				ft_exec_utils.c  \
				handle_bsq_utils.c
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
				$(CC) -g $(CFLAGS) $(INC) \
				$(addprefix $(SRC_DIR)/, $(SRC)) $(LIBFT) -o $(NAME)

clean		:
				@rm -rf $(OBJS)
				@make clean -C $(FT_DIR)

fclean		:	clean
				@echo "\nCleaning Directories..."
				rm -f $(NAME)
				@make fclean -C $(FT_DIR)

re			:	fclean all

run			:	re
				./Minishell
