CC=gcc
CCFLAGS= -Wall -Werror -g 
LIBFLAGS= 
SRC= main.c  xmlReader.c pile_char.c schedule.c file_struct.c experiment.c
SRC_TEST=  main_test.c pile_char.c xmlReader.c  experiment.c file_struct.c schedule.c
OBJ= $(SRC:.c=.o)
OBJ_TEST=$(SRC_TEST:.c=.o)
EXEC= xmlChecker



all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC)  $^ -o $@  $(LIBFLAGS)


%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

.depends:
	$(CC) -MM $(SRC) > .depends

test: $(OBJ_TEST) 
	$(CC)  $^ -o $@  $(LIBFLAGS)	


-include .depends

clean:
	rm -f $(OBJ) $(EXEC) test *.*~
