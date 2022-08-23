NC = \033[0m
RED = \033[0;91m
ORANGE = \033[93m
GREEN = \033[0;92m
PURPLE = \033[0;95m
BLUE = \033[0;34m
BOLD = \033[1m

SRCS		=	./srcs/minishell.c 

INCLUDES	=	./includes/minishell.h 

HEAD		= ./includes/

NAME		= minishell

CC			= gcc

OBJS		= ${SRCS:.c=.o}

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -lreadline



.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
		echo "${GREEN}[ OK ]	${ORANGE}${<:.s=.o}${NC}"

all:		${NAME}

${NAME}:	${OBJS}
			@${CC} ${CFLAGS} -I${HEAD} $(OBJS) ${LIBFT} -o ${NAME}
			@echo "minishell		has been created\n${NC}"


clean:
			@${RM} ${OBJS}
			@echo "${GREEN}[ OK ]${RED}	*.o files	deleted${NC}"

fclean:		clean
			@${RM} ${NAME} 
			@echo "${GREEN}[ OK ]${RED}	everything	deleted${NC}"

re :		fclean all

.PHONY:		all	clean	fclean re