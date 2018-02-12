NAME		=	cli_args.a

CC			=	gcc

RM			=	/bin/rm -f

CFLAGS		=	-Wall -Wextra -Werror -g

DIR			=	./srcs

INCLUDE		=	./includes

SRCS		=	cli_args.c argv.c options.c \
				utilities.c print.c init.c \
				free.c boolean.c integer.c \
				string.c definitions.c

OBJS		=	$(addprefix $(DIR)/, ${SRCS:.c=.o})

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@ar rc $(NAME) $^
	@ranlib $(NAME)
	@echo "\033[1;34mcli_args\t\033[1;33mCompilation\t\t\033[0;32m[OK]\033[0m"

clean:
	@$(RM) $(OBJS)
	@echo "\033[1;34mcli_args\t\033[1;33mCleaning Objects\t\033[0;32m[OK]\033[0m"

fclean:	clean
	@$(RM) $(NAME)
	@echo "\033[1;34mcli_args\t\033[1;33mFull Cleaning\t\t\033[0;32m[OK]\033[0m"

re: fclean all

.PHONY: all clean fclean re