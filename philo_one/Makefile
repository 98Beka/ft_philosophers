NAME = philo_one
P_OFILES_ONE =  actions init print main utils_1 utils_2

P_ONE_SRCS = $(addprefix srcs/, $(addsuffix .c , $(P_OFILES_ONE)))
P_ONE_OBJS = $(addprefix srcs/, $(addsuffix .o , $(P_OFILES_ONE)))

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(P_ONE_OBJS)
	@gcc $(P_ONE_OBJS) -lpthread -o $(NAME)

$(P_ONE_OBJS): %.o : %.c
	@gcc $(FLAGS) -c -I  incl/ $< -o $@

clean :
	@rm -f srcs/*.o

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: clean fclean