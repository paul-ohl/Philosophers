S		= srcs/
O		= objs/
I		= incs/
D		= deps/

CFLAGS	+= -I$I

include settings.mk

OBJS	= $(SRCS:$S%=$O%.o)
DEPS	= $(SRCS:$S%=$D%.d)

RM		= /bin/rm -rf

.PHONY: all clean fclean re

all: $(NAME)

$O:
	@mkdir $@

$(OBJS): | $O

$(OBJS): $O%.o: $S%
	$(CC) $(CFLAGS) -c $< -o $@

$D:
	@mkdir $@

$(DEPS): | $D

$(DEPS): $D%.d: $S%
	$(CC) $(CFLAGS) -MM -MF $@ -MT "$O$*.o $@" $<

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	@echo "Cleaning up... 🕸🧹"
	@$(RM) $D $O

fclean: clean
	@echo "Everything!"
	@$(RM) $(NAME)

re: fclean all

-include $(DEPS)
