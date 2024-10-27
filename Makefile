# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ledio <ledio@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 00:21:13 by ledio             #+#    #+#              #
#    Updated: 2024/10/27 23:41:41 by ledio            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I include -I libft/include -I libft/ft_printf/include
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(LIBFT_DIR)/libftprintf.a

# Color codes
RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m

# Source files for minitalk
CLIENT_SRC = src/client.c
SERVER_SRC = src/server.c

# Bonus soruce file for minitalk
BONUS_CLIENT_SRC = bonus/client_bonus.c
BONUS_SERVER_SRC = bonus/server_bonus.c

# Object files
CLIENT_OBJS = $(CLIENT_SRC:.c=.o)
SERVER_OBJS = $(SERVER_SRC:.c=.o)

# Bonus object files
BONUS_CLIENT_OBJS = $(BONUS_CLIENT_SRC:.c=.o)
BONUS_SERVER_OBJS = $(BONUS_SERVER_SRC:.c=.o)

# Main target
all: $(LIBFT) $(PRINTF) client server

# Bonus target
bonus: $(LIBFT) $(PRINTF) client_bonus server_bonus

# Compile libft
$(LIBFT) $(PRINTF):
		@echo "$(GREEN)Compiling libft and ft_printf..$(RESET)"
		@$(MAKE) -C $(LIBFT_DIR)

# Compile client
client: $(CLIENT_OBJS) $(LIBFT) $(PRINTF)
		@echo "$(GREEN)Compiling client...$(RESET)"
		$(CC) $(CFLAGS) $(INCLUDES) $(CLIENT_OBJS) -L$(LIBFT_DIR) -lftprintf -lft -o $(NAME_CLIENT)
		@echo "$(GREEN)Client compile successfully$(RESET)"

# Compile server
server: $(SERVER_OBJS) $(LIBFT) $(PRINTF)
			@echo "$(GREEN)Compiling server...$(RESET)"
			$(CC) $(CFLAGS) $(INCLUDES) $(SERVER_OBJS) -L$(LIBFT_DIR) -lftprintf -lft -o $(NAME_SERVER)
			@echo "$(GREEN)Server compiled successfully$(RESET)"

# Compile client bonus
client_bonus: $(BONUS_CLIENT_OBJS) $(LIBFT)
			@echo "$(GREEN)Compiling bonus client...$(RESET)"
			$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_CLIENT_OBJS) -L$(LIBFT_DIR) -lftprintf -lft -o $(NAME_CLIENT_BONUS)
			@echo "$(GREEN)Bonus client compiled successfully$(RESET)"

# Compile server bonus
server_bonus: $(BONUS_SERVER_OBJS) $(LIBFT)
			@echo "$(GREEN)Compiling bonus server...$(RESET)"
			$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_SERVER_OBJS) -L$(LIBFT_DIR) -lftprintf -lft -o $(NAME_SERVER_BONUS)
			@echo "$(GREEN)Bonus server compiled successfully$(RESET)"

# Compile individual object files
%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
		@echo "$(RED)Removing executables...$(RESET)"
		@rm -f $(CLIENT_OBJS) $(SERVER_OBJS) $(BONUS_CLIENT_OBJS) $(BONUS_SERVER_OBJS)
		@$(MAKE) -C $(LIBFT_DIR) clean
		@echo "$(GREEN)Removed successfully..$(RESET)"

# Remove executables and object files
fclean:
		@echo "$(RED)Removing executables..$(RESET)"
		@rm -f $(NAME_CLIENT) $(NAME_SERVER) $(CLIENT_OBJS) $(SERVER_OBJS)
		@rm -f $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS) $(BONUS_CLIENT_OBJS) $(BONUS_SERVER_OBJS)
		@$(MAKE) -C $(LIBFT_DIR) fclean
		@echo "$(GREEN)Removed successfully..$(RESET)"

# Rebuilding everything
re: fclean all

.PHONY: all clean fclean re bonus