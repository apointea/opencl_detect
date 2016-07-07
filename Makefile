# --- COLOR --- #
RED=\033[31m[-]
GREEN=\033[32m[+]
YELLOW=\033[33m[!]
BLUE=\033[34m[*]
MAGENTA=\033[35m
CYAN=\033[36m[*]
CLEAR=\033[0m

# --- GENERAL --- #
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra

# --- PRODUCT --- #
IDENTIFIER	= OPENCL_DEVICES
NAME		= opencl_devices

# --- SOURCES --- #
SRCS_DIR	= ./srcs/
SRCS		= main.c

OBJS_DIR	= ./objs/
OBJS		= $(SRCS:.c=.o)

# --- INCLUDES --- #
FRAMEWORK	= -framework OpenCL

# --- RULES --- #
all: $(NAME)

$(NAME): $(addprefix $(OBJS_DIR), $(OBJS))
	@printf "$(CYAN) $(IDENTIFIER) $(CLEAR)Link $(@)\n"
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(FRAMEWORK)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@if [ ! -d $(OBJS_DIR) ]; then mkdir $(OBJS_DIR); fi
	@printf "$(BLUE) $(IDENTIFIER) $(CLEAR)Compiling $(<)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(YELLOW) $(IDENTIFIER) $(CLEAR)delete $(OBJS_DIR)\n"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@printf "$(YELLOW) $(IDENTIFIER) $(CLEAR)delete $(NAME)\n"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
