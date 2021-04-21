ifndef SETTINGS_MK
	SETTINGS_MK = 1

NAME	= philo_two
SRCS	= $Smain.c $Smake_action.c $Sphilo_checks.c

CC		= gcc
CFLAGS	+= -Wall -Wextra -Werror
LDFLAGS	+= 

endif
