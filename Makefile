NAME =			minishell

# SOURCES
SRC =			$(SRC_NAME)
SRC_PATH =		sources/

SRC_NAME =		main.c func_env.c get_next_line.c get_next_line_utils.c func_export.c error.c func_cd.c \
				utils.c  ast_func.c cmd.c lexer.c process_request.c run_tree.c execute.c \
				func_echo.c	func_pwd.c	func_unset.c	func_execve.c	func_dollar.c \
				parse_cmd.c parse_command_line.c parse_job.c parse_token.c parse.c utils_bis.c run_tree_bis.c \
				lexer_utils.c lexer_bis.c func_utils.c cmd_bis.c parse_cmd_bis.c func_env_bis.c \
				func_utils_redirect.c

LIB			=	libft/libft_linux.a
LIBMAC		=	libft/libft.a

# HEADER
HEAD_PATH =		includes

# All .o (object file)
OBJS_PATH =		objs/
OBJS =			$(SRC:%.c=$(OBJS_PATH)%.o)

# Compilation
GCC =			gcc

# Compilation flags
GCCFLAGS =		-Werror -Wall -Wextra 


all:			$(OBJS)
				@$(GCC) $(GCCFLAGS) $(OBJS) $(LIB) -o $(NAME)
				@export > objs/export.txt
				@echo "\033[1;32mDone !\033[m"

mac:			$(OBJS)
				@$(GCC) $(GCCFLAGS) $(OBJS) $(LIBMAC) -o $(NAME)
				@export > objs/export.txt
				@echo "\033[1;32mDone !\033[m"
				
$(NAME):	all

# Getting .o from .c rule
$(OBJS_PATH)%.o: $(SRC_PATH)%.c
				@$(GCC) $(GCCFLAGS) -I $(HEAD_PATH) -c $< -o $@

$(OBJS):		$(OBJS_PATH)

$(OBJS_PATH):
				@echo "\033[1;32mCompiling minishell...\033[m"
				@mkdir $(OBJS_PATH)


fclean:
				@rm -rf $(OBJS_PATH) $(NAME)
				@echo "\033[1;31mDeleting minishell...\033[m"
clean:
				@rm -rf $(OBJS_PATH)
				@echo "\033[1;31mDeleting objects...\033[m"

re:				fclean all

.PHONY:			all clean fclean re