NAME = philo
CC = cc
SRCDIR = ./srcs
OBJDIR = ./objs
HEADDIR = ./includes
FLAGS = -g -Wall -Wextra -Werror -fsanitize=thread
HEADER = philo.h

SRC = $(wildcard $(SRCDIR)/*.c)

OBJ = $(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))

all:    $(NAME)

$(OBJDIR)/%.o :	$(SRCDIR)/%.c $(HEADDIR)/$(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME):	$(OBJDIR) $(OBJ)
		$(CC) $(FLAGS) -pthread -o $(NAME) -I $(HEADDIR)/$(HEADER) $(OBJ)

$(OBJDIR):
		@if [ ! -d $(OBJDIR) ] ; then echo "creating $(OBJDIR)" ; mkdir $(OBJDIR); fi

clean:
		@if [ -d $(OBJDIR) ] ; then echo "deleting $(OBJDIR)" ; rm -r $(OBJDIR); fi
fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
