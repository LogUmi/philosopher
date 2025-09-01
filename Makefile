NAME = 	philo.a
EXEC =	philo
DIRSR = srcs/
DIROB = objs/
DIRLI = includes/
FILEH = philo.h
FILEC = philo.c  \
		utils.c \
		init.c \
		liberation.c \
		simulation.c \
		philosophers.c \
		supervisor.c \
		var_mutex.c

SRCS =	$(addprefix $(DIRSR), $(FILEC))
OBJS =	$(addprefix $(DIROB), $(FILEC:.c=.o))
HDRS =	$(addprefix $(DIRLI), $(FILEH))
FLAGS = -Wall -Werror -Wextra
CC = cc
AR = ar -rcs

all:		$(NAME) $(EXEC)

$(NAME):	$(OBJS)	$(HDRS) #$(LIBR)
			$(AR) $(NAME) $(OBJS)	

# Compilation des fichiers .o dans obj/
$(DIROB)%.o: $(DIRSR)%.c | $(DIROB)
	$(CC) $(FLAGS) -I. -c $< -o $@ 

# Création du dossier obj/ si nécessaire
$(DIROB):
			mkdir -p $(DIROB)

$(EXEC):	$(SRCS) $(HDRS)
			$(CC) $(FLAGS) $(SRCS) $(NAME) -I.$(DIRLI) -o $(EXEC) -g

clean:		
			rm -rf	$(OBJS)

fclean:		clean
			rm -rf $(NAME) $(EXEC)	

re:			fclean all

.PHONY:		all clean fclean re
