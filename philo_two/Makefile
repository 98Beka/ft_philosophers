NAME = philo_two
P_OFILES_TWO =  actions init print main utils_1 utils_2

P_TWO_SRCS = $(addprefix srcs/, $(addsuffix .c , $(P_OFILES_TWO)))
P_TWO_OBJS = $(addprefix srcs/, $(addsuffix .o , $(P_OFILES_TWO)))

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(P_TWO_OBJS)
	@gcc $(P_TWO_OBJS) -lpthread -o $(NAME)

$(P_TWO_OBJS): %.o : %.c
	@gcc $(FLAGS) -c -I  incl/ $< -o $@

clean :
	@rm -f srcs/*.o

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: clean fclean