all:
	gcc -Ofast src/cm8.c src/bit.c src/attackTables.c src/inputProcessor.c src/driver.c src/randomizingRoutines.c src/moveGenerator.c -o cm8.exe
	gcc -Ofast src/cm8.c src/bit.c src/attackTables.c src/inputProcessor.c src/driver.c src/randomizingRoutines.c src/moveGenerator.c -o cm8.out
exe:
	gcc -Ofast src/cm8.c src/bit.c src/attackTables.c src/inputProcessor.c src/driver.c src/randomizingRoutines.c src/moveGenerator.c -o cm8.exe
out:
	gcc -Ofast src/cm8.c src/bit.c src/attackTables.c src/inputProcessor.c src/driver.c src/randomizingRoutines.c src/moveGenerator.c -o cm8.out
debug:
	gcc -g src/cm8.c src/bit.c src/attackTables.c src/inputProcessor.c src/driver.c src/randomizingRoutines.c src/moveGenerator.c -o cm8d.exe
	gcc -g src/cm8.c src/bit.c src/attackTables.c src/inputProcessor.c src/driver.c src/randomizingRoutines.c src/moveGenerator.c -o cm8d.out
debugexe:
	gcc -g src/cm8.c src/bit.c src/attackTables.c src/inputProcessor.c src/driver.c src/randomizingRoutines.c src/moveGenerator.c -o cm8d.exe
debugout:
	gcc -g src/cm8.c src/bit.c src/attackTables.c src/inputProcessor.c src/driver.c src/randomizingRoutines.c src/moveGenerator.c -o cm8d.out
clean:
	del cm8.exe
	del cm8d.exe
	del cm8.out
	del cm8d.out
rune:
	./cm8.exe
runo:
	./cm8.out
runde:
	./cm8d.exe
rundo:
	./cm8d.out
quick:
	make exe
	make rune