# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vintz <vintz@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/14 23:49:27 by vvaucoul          #+#    #+#              #
#    Updated: 2022/01/27 14:59:11 by vintz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILATION ###
CC				= clang
CFLAGS			= -I $(HEADER) -Wall -Wextra -Werror # -g3 -pg -fno-builtin

### EXECUTABLE ###
NAME			= ft_ls

### INCLUDES ###
HEADER 			= ./includes/
SRC_PATH 		= srcs
OBJS_DIR		= objs

### SOURCES ###

SRCS			=	$(SRC_PATH)/main.c \
					$(SRC_PATH)/utils/utils_alloc.c \
					$(SRC_PATH)/utils/utils.c \
					$(SRC_PATH)/utils/utils_array.c \
					$(SRC_PATH)/utils/utils_display.c \
					$(SRC_PATH)/utils/utils_str.c \
					$(SRC_PATH)/core/readcases.c \
					$(SRC_PATH)/core/display_utils.c \
					$(SRC_PATH)/core/sortdir.c \
					$(SRC_PATH)/core/readdir.c \
					$(SRC_PATH)/core/readfiles.c \
					$(SRC_PATH)/core/files_utils.c \
					$(SRC_PATH)/core/display_dir_info.c \
					$(SRC_PATH)/parsing/parse.c

### OBJECTS ###
OBJS			=	$(SRCS:.c=.o)

### PRINT UTILS ###
PRINT_COMP		=	printf "\r$(_BOLD)$(_WHITE)- $(_BOLD)$(_CYAN)[%s]\r\t\t\t\t $(_BOLD)$(_WHITE)[✓]\n"

%.o : %.c
	@echo -n "\r                                                               "
	@$(PRINT_COMP) $@
	@$(CC) $(CFLAGS) -I. -c $< -o ${<:.c=.o}



################################################################################
#								 	 COLORS				  					   #
################################################################################

# This is a minimal set of ANSI/VT100 color codes
_END=$'\033[0m
_BOLD=$'\033[1m
_UNDER=$'\033[4m
_REV=$'\033[7m

# Colors
_GREY=$'\033[30m
_RED=$'\033[31m
_GREEN=$'\033[32m
_YELLOW=$'\033[33m
_BLUE=$'\033[34m
_PURPLE=$'\033[35m
_CYAN=$'\033[36m
_WHITE=$'\033[37m

# Inverted, i.e. colored backgrounds
_IGREY=$'\033[40m
_IRED=$'\033[41m
_IGREEN=$'\033[42m
_IYELLOW=$'\033[43m
_IBLUE=$'\033[44m
_IPURPLE=$'\033[45m
_ICYAN=$'\033[46m
_IWHITE=$'\033[47m


### CLEAN ###
RM				= rm -f

### RULES ###

all:			$(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	@echo "\n\t$(_BOLD)$(_WHITE)- $(_GREEN)FT_LS COMPILED ! $(_BOLD)$(_WHITE)-$(NOC)"
clean:
	@$(RM) -r $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

leaks:
	valgrind ./ft_ls Makefile srcs -lRart

.PHONY: all clean fclean re leaks
