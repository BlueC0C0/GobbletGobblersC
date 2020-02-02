game: verif.o other.o main.o display.o board.o core.o bot.o save.o init.o
	gcc verif.o other.o main.o display.o board.o core.o bot.o save.o init.o -o game

main.o: main.c definition.h board.h
	gcc main.c -c

verif.o: verif.c definition.h board.h
	gcc verif.c -c

other.o: other.c definition.h
	gcc other.c -c

display.o: display.c board.h definition.h
	gcc display.c -c

core.o: core.c board.h definition.h
	gcc core.c -c

save.o: save.c board.h definition.h save.h
	gcc save.c -c

bot.o: bot.c board.h definition.h bot.h
	gcc bot.c -c

init.o: init.c definition.h bot.h save.h
	gcc init.c -c

clean:
	rm -rf [!b]*.o

run:
	./game
