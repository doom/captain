
POC	=	poc

SRCS	=	captain.c main.c
OBJS	=	$(SRCS:.c=.o)

CC	=	gcc
CFLAGS	=	-Wall -Wextra

RM	=	rm -f

all:		$(POC)

$(POC):		$(OBJS)
		@$(CC) -o $(POC) $(OBJS)

clean:
		$(RM) $(OBJS) $(POC)
