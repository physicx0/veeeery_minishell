CC = cc
CFLAGS = -Wall -Wextra -Werror
CFILES = main.c exec/here_doc.c exec/check_path_I.c exec/exec_utils.c exec/safe_syscalls.c exec/builtins_I.c exec/unset.c exec/export.c exec/linked_list.c exec/utils.c exec/utils_I.c exec/utils_II.c exec/exit.c exec/builtins.c exec/execution.c exec/signals.c exec/check_path.c exec/get_args.c exec/redirection.c exec/split.c parsing/minishell.c parsing/expanding.c  utils/utils_0.c utils/utils_1.c  utils/utils_2.c utils/utils_3.c utils/utils_4.c utils/org_helper.c utils/cmd_spliter.c utils/spliter_helper.c utils/tokenize.c utils/free_head.c utils/parse_helper.c utils/expan_help.c parsing/syntax_checker_0.c parsing/syntax_checker_1.c parsing/parse.c parsing/heredoc_expand.c

OFILES = $(CFILES:.c=.o)
NAME = minishell
RDLIB = -L/Users/amaaouni/.brew/opt/readline/lib
RDINC = -I/Users/amaaouni/.brew/opt/readline/include

all: $(NAME)
$(OFILES): %.o: %.c includes/minishell.h exec/exec.h
	$(CC) $(CFLAGS) -c $< -o $@
$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(RDINC) $(OFILES) -lreadline $(RDLIB) -o $(NAME)
clean:
	rm -rf $(OFILES)
fclean: clean
	rm -rf $(NAME)
re: fclean $(NAME)
