NAME = philo_three
P_OFILES_THREE =  actions init print main utils_1 utils_2

P_THREE_SRCS = $(addprefix srcs/, $(addsuffix .c , $(P_OFILES_THREE)))
P_THREE_OBJS = $(addprefix srcs/, $(addsuffix .o , $(P_OFILES_THREE)))

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(P_THREE_OBJS)
	@gcc $(P_THREE_OBJS) -lpthread -o $(NAME)

$(P_TWO_OBJS): %.o : %.c
	@gcc $(FLAGS) -c -I  incl/ $< -o $@

clean :
	@rm -f srcs/*.o

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: clean fclean