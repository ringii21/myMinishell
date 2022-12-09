# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ringii <ringii@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/07 19:14:12 by seozcan           #+#    #+#              #
#    Updated: 2022/12/09 17:40:35 by ringii           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::PATHS::

PROJ			:=	beab_sh

ODIR			:=	$(addprefix $(PROJ)/,objs)

SDIR			:=	$(addprefix $(PROJ)/,srcs)

IDIR			:=	$(addprefix $(PROJ)/,inc)

LDIR 			:=	libft

PFDIR			:=	printf

MDIR			:=	minilibx-linux

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::TARGET::

NAME			:=	minishell

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::SOURCES::

SRCS			:=	main.c \
					shell_builtins.c \
					shell_cd.c \
					shell_echo.c \
					shell_env.c \
					shell_exit.c \
					shell_expansion.c \
					shell_export.c \
					shell_flush.c \
					shell_init.c \
					shell_io.c \
					shell_jobs.c \
					shell_parsing.c \
					shell_path.c \
					shell_pipes.c \
					shell_redir.c \
					shell_signals.c \
					shell_structs.c \
					shell_unset.c \
					utils_builtins.c \
					utils.c \
					utils_export.c \
					heredoc.c \
					utils_env.c

OBJS			=	$(addprefix $(ODIR)/, $(SRCS:.c=.o))

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::COMPILERS::

CC				:=	clang

WFLAGS			:=	-MMD -Wall -Wextra -Werror

WCONV 			:=	-Wconversion

GFLAG			:=	-g3

SANFLAG			:=	-fsanitize=address

AR				:=	ar

ARFLAGS			:=	rcs

MLXFLAGS		:=	-lXext -lX11

MATHFLAG		:=	-lm

READLINE		:=	-lreadline

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::HEADERS::

LINC			=	$(addprefix $(LDIR)/, $(IDIR))

PFINC			=	$(addprefix $(PFDIR)/, $(IDIR))

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::LIBRARY::

IS_LIBFT		:=	true

LIB				:=	$(addprefix $(LDIR)/, libft.a)

LIBTF_PATH		=	$(addprefix $(LDIR)/, ${LIB})

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::printf::

IS_PRINTF		:=	false

PRINTF			:=	libftprintf.a

PRINTF_PATH		=	$(addprefix $(PFDIR)/, $(PRINTF))

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::MINILIBX::

IS_MINILIBX		:=	false

MINILIBX		:=	libmlx_Linux.a

MINILIBX_PATH	=	$(addprefix $(MDIR)/, ${MINILIBX})

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

# ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::PARAMS::

INCLUDE_FLAGS		=	$(addprefix -I , $(IDIR))

ifeq ($(IS_LIBFT),true)
	INCLUDE_FLAGS	+=	$(addprefix -I , $(LINC))
endif

ifeq ($(IS_PRINTF), true)
	INCLUDE_FLAGS	+= $(addprefix -I , $(PFINC))
endif

ifeq ($(IS_MINILIBX), true)
	INCLUDE_FLAGS	+= $(addprefix -I , $(MDIR))
endif

DEPS				= $(OBJS:.o=.d)

vpath %.c $(SDIR)\
vpath %.o $(ODIR)\

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::MANDATORY::

all:			header lib h2 message $(NAME)

$(ODIR)/%.o:	%.c 
	@$(CC) $(WFLAGS) $(WCONV) $(INCLUDE_FLAGS) -c $< -o $@ 
	@echo "$(HIGREEN)compilation:\t\t\t\t\t\t[OK]$(NO_COLOR)"

$(NAME):		$(OBJS)	
	@$(CC) $(WFLAGS) $(WCONV) $(SANFLAG) $(GFLAG) $(INCLUDE_FLAGS) $(READLINE) $(OBJS) $(LIB) -o $(NAME)
	@echo "$(HIGREEN)$(NAME) executable:\t\t\t\t\t[OK]$(NO_COLOR)"

$(OBJS):		| $(ODIR)

$(ODIR):
	@mkdir -p $(ODIR)
	@echo "$(HIGREEN)objs folder:\t\t\t\t\t\t[OK]$(NO_COLOR)"

# :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::RULES::

update:		header fclean
	@git pull

push:		header fclean fcleanlib
	@echo "$(HIGREEN)"
	@git add .
	@git commit --quiet
	@git push --quiet
	@echo "$(HIGREEN)git push:\t\t\t\t\t\t[OK]$(NO_COLOR)"

clean:		header
	@rm -rf $(ODIR)
	@echo "$(HIORANGE)objs folder:\t\t\t\t\t\t[RM]$(NO_COLOR)"

fclean:		header clean
	@rm -f $(NAME)
	@echo "$(HIORANGE)$(NAME) executable:\t\t\t\t\t[RM]$(NO_COLOR)"

lib:
ifeq ($(IS_LIBFT),true)
	@make -C $(LDIR) --quiet
endif
ifeq ($(IS_PRINTF),true)
	@make -C $(PFDIR) --quiet
endif
ifeq ($(IS_MINILIBX),true)
	@make -C $(MDIR) --quiet 
endif

relib:	header
ifeq ($(IS_LIBFT),true)
	@make -C $(LDIR) --quiet re
endif
ifeq ($(IS_PRINTF),true)
	@make -C $(PFDIR) --quiet re
endif
ifeq ($(IS_MINILIBX),true)
	@make -C $(MDIR) --quiet re
endif

fcleanlib:	header
ifeq ($(IS_LIBFT),true)
	@make -C $(LDIR) --quiet fclean
endif
ifeq ($(IS_PRINTF),true)
	@make -C $(PFDIR) --quiet fclean
endif
ifeq ($(IS_MINILIBX),true)
	@make -C $(MDIR) --quiet clean
endif

header:
	@echo "$(BHIPURPLE)"
	@echo "   ______________________________________________________"
	@echo "  /\     __________    ________    ___   ___    _______  \ "
	@echo " /  \   /\         \  /\   __  \  /\  \ /\  \  /\  ____\  \ "
	@echo "/    \  \ \  \ _/\  \ \ \   __  \ \ \  \ /_ /_ \ \  _\_/_  \ "
	@echo "\     \  \ \__\_/ \__\ \ \__\-\__\ \ \__\  \__\ \ \______\  \ "
	@echo " \     \  \/__/  \/__/  \/__/ /__/  \/__/ \/__/  \/______/   \ "
	@echo "  \     \_____________________________________________________\ "
	@echo "   \    /                                                     / "
	@echo "    \  /         $(CYAN) A B O N A R D  &&  S E O Z C A N \$(NO_COLOR)$(BHIPURPLE)   ____   / "
	@echo "     \/______________________________________________/\   \_/ "
	@echo "                                                     \ \___\ "
	@echo "                                                      \/___/ "
	@echo "$(NO_COLOR)"

h2:
	@echo "\n$(BHIPURPLE):::::::::::::::::::::::::::::::::::::::::::::::::MINISHELL::\n$(NO_COLOR)"

message:
	@make -q $(NAME) && echo "$(BHIGREEN)All files are already up to date$(NO_COLOR)" || true

message_b:
	@make -q $(BNAME) && echo "$(BHIGREEN)All bonus files are already up to date$(NO_COLOR)" || true

re:		header fclean fcleanlib all 

-include $(DEPS)

.PHONY:	all bonus clean fclean re push update o_dir h1 h2 header 
