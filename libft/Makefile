# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seozcan <seozcan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/07 19:14:12 by seozcan           #+#    #+#              #
#    Updated: 2022/12/16 20:50:59 by seozcan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::TARGET::

NAME	:= libft.a

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::SOURCES::

SDIR	:= srcs

SRCS	:= 	ft_allocate_tab.c \
			ft_atoi.c \
			ft_atoi_hexa.c \
			ft_atoli.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_error.c \
			ft_free_stab.c \
			ft_free_tab.c \
			ft_gnl.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_multi_split.c \
			ft_node_addback.c \
			ft_node_addfront.c \
			ft_nodeclear.c \
			ft_node_delone.c \
			ft_node_iter.c \
			ft_node_last.c \
			ft_nodemap.c \
			ft_nodenew.c \
			ft_node_size.c \
			ft_print_stab.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_stack_free.c \
			ft_stack_init.c \
			ft_stack_push.c \
			ft_stack_putback.c \
			ft_stack_putfront.c \
			ft_stack_reverse.c \
			ft_stack_rotate.c \
			ft_stack_size.c \
			ft_stack_swap.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdup.c \
			ft_strisdigit.c \
			ft_striteri.c \
			ft_strjoin_free.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tablen.c \
			ft_tolower.c \
			ft_toupper.c 

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::OBJECTS::

ODIR	:= objs

OBJS	=  $(addprefix $(ODIR)/, $(SRCS:.c=.o))

DEPS	= $(OBJS:.o=.d)

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::COMPILERS::

CC		:= clang

WFLAGS	:= -MMD -Wall -Wextra -Werror 

WCONV 	:= -Wconversion

GFLAG	:=  -g3

SANFLAG	:= -fsanitize=address

AR		:= ar

ARFLAGS	:= rcs

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::HEADERS::

IDIR	:= inc

INC		:= libft.h

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::COLORS::

NO_COLOR		=	\033[m

BLACK			=	\033[0;30m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
ORANGE 		 	=	\033[0;33m
BLUE			=	\033[0;34m
PURPLE			=	\033[0;35m
CYAN			=	\033[0;36m
WHITE			= 	\033[0;37m

# High Intensty
HIGREEN			=	\033[0;92m
HIORANGE	 	=	\033[0;93m
HIPURPLE		=	\033[0;95m

# Bold
BORANGE 		=	\033[1;33m
BBLUE			=	\033[1;34m
BPURPLE			=	\033[1;35m
BCYAN			=	\033[1;36m

# Bold High Intensity
BHIGREEN		=	\033[1;92m
BHIORANGE	 	=	\033[1;93m
BHIPURPLE		=	\033[1;95m

# Italic
ICYAN			=	\033[3;36m

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::RULES::

vpath %.c $(SDIR)
vpath %.o $(ODIR)

all:			header message $(NAME)

$(ODIR)/%.o:	%.c
	@$(CC) $(WFLAGS) $(GFLAG) -I $(IDIR) -c $< -o $@
	@echo "$(HIGREEN)libft compilation:\t\t\t\t\t[OK]$(NO_COLOR)"

$(NAME):		$(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo "$(HIGREEN)$(NAME):\t\t\t\t\t\t[OK]$(NO_COLOR)"

$(OBJS):		| $(ODIR)

$(ODIR):
	@mkdir -p $(ODIR)
	@echo "$(HIGREEN)libft objs folder:\t\t\t\t\t[OK]$(NO_COLOR)"

clean:
	@rm -rf $(ODIR)
	@echo "$(HIORANGE)objs folder:\t\t\t\t\t\t[RM]$(NO_COLOR)"

fclean:		clean
	@rm -f $(NAME)
	@echo "$(HIORANGE)$(NAME):\t\t\t\t\t\t[RM]$(NO_COLOR)"

header:
	@echo "\n$(BHIPURPLE):::::::::::::::::::::::::::::::::::::::::::::::::::::LIBFT::\n$(NO_COLOR)"

message:
	@make -q $(NAME) && echo "$(BHIGREEN)All files are already up to date\n$(NO_COLOR)" || true

re:		fclean all

-include $(DEPS)

.PHONY:	all clean fclean re