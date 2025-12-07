# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 15:53:34 by dufama            #+#    #+#              #
#    Updated: 2025/12/07 17:46:08 by dufama           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = pipex.c \
		srcs/path.c \
		srcs/utils.c \
		srcs/error.c \
		srcs/process.c \
		srcs/open_file.c \
		srcs/utils2.c \

SRCS_BONUS = pipex_bonus.c \
				srcs/path.c \
				srcs/utils.c \
				srcs/error.c \
				srcs/process.c \
				srcs/open_file.c \
				srcs/utils2.c \
				srcs/process_bonus.c \
				srcs/utils_bonus.c \
				srcs/read_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

NAME = pipex

BONUS = pipex_bonus

CC = cc -g
CFLAGS = -Wall -Werror -Wextra -I ./
RM = rm -f

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(MAKE) -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(BONUS): $(OBJS_BONUS)
	@$(MAKE) -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(BONUS)

all: $(NAME)

bonus: $(BONUS)

clean:
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME) $(BONUS)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
