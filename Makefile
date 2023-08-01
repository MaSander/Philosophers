NAME=philosophers

SOURCES=main.c utils.c error.c philo_life.c

OBJS=$(SOURCES:.c=.o)

FLAGS=-Wall -Wextra -Werror

COMPILER=cc

HEADERS=philosophers.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) -c $(FLAGS) $< -o $@

clean:
	rm -rf *.o

fclean:	clean
	rm -rf philosophers

re:	fclean all