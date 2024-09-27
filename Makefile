CC = cc
CFLAGS = -fsanitize=address
CFILES = exec/execution.c exec/check_path.c exec/libft.c exec/get_args.c exec/redirection.c exec/split.c parsing/minishell.c parsing/expanding.c  utils/utils_1.c  utils/cmd_spliter.c utils/utils.c utils/tokenize.c utils/parse_helper.c parsing/syntax_checker_0.c parsing/syntax_checker_1.c parsing/parse.c 
OFILES = $(CFILES:.c=.o)
NAME = minishell
all: $(NAME)
$(OFILES): %.o: %.c includes/minishell.h
	$(CC) -c $< -o $@
$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -lreadline -o $(NAME)
clean:
	rm -rf $(OFILES)
fclean: clean
	rm -rf $(NAME)
re: fclean $(NAME)
