NAME = minishell
CC = cc
FLAGS = -Wall -Werror -Wextra -g
READLINE_PATH = /Users/mazaroua/homebrew/Cellar/readline/8.2.1
IFLAG = -I $(READLINE_PATH)/include/readline
LFLAG = -L $(READLINE_PATH)/lib -lreadline
SRC = minishell.c utils.c remove_spaces.c tokenizer.c tokenizer_utils.c tokenizer_utils2.c tokenizer_utils3.c syntax.c parser.c parser2.c parser_utils.c expander.c \
		execution.c execution_2.c execution_utils.c cdpwd.c redirections.c redirections_2.c ft_heredoc.c execution_main_utils.c \
		init_env.c export.c unset.c echo.c exit.c export_utils1.c  export_utils2.c export_utils3.c export_utils4.c init_env_utils.c \
		utils3.c utils4.c utils5.c ft_split.c garbage_collector.c shlvl.c execution_utils3.c export_utils6.c export_utils5.c unset_utils.c exit_utils.c \
		signal.c utils6.c
OBJ = $(SRC:.c=.o)


all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(FLAGS) $(LFLAG) $(OBJ) -o $(NAME)

%.o:%.c minishell.h
	$(CC) $(FLAGS) -c $(IFLAG)  $< -o $@

clean:
	rm -rf *.o

fclean:clean
	rm -rf $(NAME)

re:fclean all

.PHONY: all fclean clean   
