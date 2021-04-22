# Folders and Names
NAME		= philo_one
SRCSDIR		= srcs
OBJSDIR		= objs
INCLUDES	= incs
EXTLIB		= libft

SRCS		= main.c \
			  output/errors.c output/print_status.c \
			  preparatory/initializations.c preparatory/input_checks.c \
			  thread_actions/philo_act.c thread_actions/threads.c \
			  thread_actions/controller_act.c thread_actions/eating.c \
			  utils/time.c utils/free.c

# Compiler options
CC			= gcc
CFLAGS		= -Wall -Wextra -g3 -fsanitize=address

###################################################
# The rest is done by the MakeFile automatically, #
# you should not have to modify it				  #
###################################################

OBJS	= $(SRCS:%.c=$(OBJSDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(EXTLIB)/$(EXTLIB).a
	@echo "Assembling $@"
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS): $(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(@D)
	@echo Compiling $<
	@$(CC) $(CFLAGS) -I$(INCLUDES) -I$(EXTLIB)/incs -c $< -o $@

$(EXTLIB)/$(EXTLIB).a:
	@echo "Compiling $@"
	@$(MAKE) -s -C $(EXTLIB) > /dev/null

clean:
	rm -rf $(OBJSDIR)
	@$(MAKE) -s -C $(EXTLIB) clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -s -C $(EXTLIB) fclean

re: fclean all

test: all
	./$(NAME)

.PHONY: all clean fclean re test bonus
