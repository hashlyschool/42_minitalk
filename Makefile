NAME_SERVER	= server
NAME_CLIENT	= client
CC			= clang
FLAGS		= -O2 -Wall -Wextra -Werror
RM			= rm -rf
INC_PATH	= ./
SRCS_PATH	= ./
OBJS_PATH	= ./
SRCS_NAME	= ft_server.c ft_client.c
INC			= ./ft_minitalk.h
LIBFT		= libft/libft.a

SRC			= $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS		= $(addprefix $(OBJS_PATH), $(SRCS_NAME:.c=.o))

all: libft $(NAME_SERVER) $(NAME_CLIENT)

libft:
	make -C ./libft

$(NAME_SERVER): $(INC) $(OBJS)
	$(CC) $(FLAGS) ft_server.o $(LIBFT) -o $(NAME_SERVER)

$(NAME_CLIENT): $(INC) $(OBJS)
	$(CC) $(FLAGS) ft_client.o $(LIBFT) -o $(NAME_CLIENT)

clean: clean_libft
	$(RM) $(OBJS)

clean_libft:
	make clean -C ./libft

fclean:	clean fclean_libft
	$(RM) $(NAME_SERVER) $(NAME_CLIENT)

fclean_libft:
	$(RM) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re libft