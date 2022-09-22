NAME = philo
HEADER = philo.h
SRC =  actions check clean main philo_utils_00 philo_utils_01 libft
OBJ = $(addsuffix .o, $(SRC))
FLAGS = -Werror -Wextra -Wall
GCC = cc

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(GCC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HEADER)
	$(GCC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re