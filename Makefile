##########################################################
#					Instructions						 #
##########################################################

NAME =  minishell
CFLAGS = -Wall -Werror -Wextra  -g -fsanitize=address 
CC = cc 

##########################################################
#					SOURCES AND OBJS					 #
##########################################################

SRCS =  main/minishell.c main/signals.c\
		utils/env.c utils/get_next_line.c utils/free_utils.c\
		parser/syntax.c parser/syntax_utils.c \
		parser/expander.c parser/expander_utils.c \
		parser/parse.c parser/redirection.c parser/quote_utils.c \
		parser/comand_list_utils.c parser/heredoc.c \
		builtins/builtins.c builtins/do_export.c builtins/utils.c builtins/utils_2.c\
		builtins/builtins_2.c builtins/do_cd.c builtins/do_exit.c\
		executor/executor.c\
		executor/utils_executor.c\
		executor/utils_execve.c \
		
INCLUDES = includes

OBJS :=$(SRCS:.c=.o)

##########################################################
#					CODIGOS ANSI						 #
##########################################################


CLR_RMV		= \033[0m
RED		    = \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
CLEARBLUE	= \033[1;94m
CYAN 		= \033[1;36m
PURPLE		= \033[1;35m
WHITE 		= \033[1;37m
BLACK 		= \033[1;30m
GREY 		= \033[0;37m

##########################################################

all: $(NAME)

$(NAME) : $(OBJS)
	@make -C ./libft/ --silent --no-print-directory
	$(CC) $(CFLAGS) $(^) libft/libft.a -lreadline -o $(@)
	@clear
	@echo "$(GREEN)Compilation of ${CLR_RMV}${CYAN}$(NAME): ${CLR_RMV}$(GREEN)⭐️"
	@echo "$(CYAN)$(NAME) ${CLR_RMV}$(GREEN)created with sucess ${CLR_RMV} ✔️"

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $(^) -o $(@)

clean:
	rm -f $(OBJS)
	make clean -C ./libft/
	clear
	@echo "$(RED)Deleting🗑 $(PURPLE)-> $(YELLOW)$(NAME) $(CLR_RMV)$(RED)[objs]$(GREEN) ✔️${CLR_RMV}"

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft/
	clear
	@echo "$(RED)Deleting🗑 $(PURPLE)-> $(YELLOW)$(NAME) $(CLR_RMV)$(RED)[objs] $(GREEN)✔️${CLR_RMV}"

re: fclean all

.PHONY: all clean fclean re
