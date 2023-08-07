NAME=philosophers

SOURCES=main.c philosophers.c utils.c error.c life.c timer.c annotation.c monitoring.c

OBJECTS_DIR=objects

OBJECTS=$(SOURCES:%.c=$(OBJECTS_DIR)/%.o)

FTFLAGS=-Wall -Wextra -Werror

FLAGS=-pthread

COMPILER=cc

HEADER=philosophers.h

$(OBJECTS_DIR)/%.o:	%.c $(HEADER)
	$(CC) $(FTFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJECTS_DIR) $(OBJECTS) $(HEADER)
	$(CC) $(FTFLAGS) $(OBJECTS) $(FLAGS) -o $(NAME)

$(OBJECTS_DIR):
	mkdir -p $(OBJECTS_DIR)

clean:
	rm -rf $(OBJECTS_DIR)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all