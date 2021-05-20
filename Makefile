P_OFILES =  actions init logs main time tools utils_1

P_ONE_SRCS = $(addprefix philo_one/srcs/, $(addsuffix .c , $(P_OFILES)))
P_ONE_OBJS = $(addprefix philo_one/srcs/, $(addsuffix .o , $(P_OFILES)))

FLAGS = -Wall -Wextra -Werror

all: $(P_ONE_OBJS)
	@gcc $(P_ONE_OBJS) -lpthread -o one

$(P_ONE_OBJS): %.o : %.c
		@gcc $(FLAGS) -c -I  philo_one/incl/ $< -o $@
		
clean :
	@rm -f philo_one/srcs/*.o

fclean : clean
	@rm -f one

re : fclean p_one p_two_l p_two_m p_three

.PHONY: clean fclean p_one p_two_l p_two_m p_three save get