all:
	gcc -Ofast src/cm8.c src/bit.c src/attackTables.c src/inputProcessor.c src/driver.c src/randomizingRoutines.c -o cm8.exe
	gcc -Ofast src/cm8.c src/bit.c src/attackTables.c src/inputProcessor.c src/driver.c src/randomizingRoutines.c -o cm8.out
debug:
	gcc -g src/cm8.c src/bit.c src/attackTables.c src/inputProcessor.c src/driver.c src/randomizingRoutines.c -o cm8d.exe
	gcc -g src/cm8.c src/bit.c src/attackTables.c src/inputProcessor.c src/driver.c src/randomizingRoutines.c -o cm8d.out
clean:
	del cm8.exe
	del cm8d.exe
	del cm8.out
	del cm8d.out
runw:
	./cm8.exe
runl:
	./cm8.out
rundw:
	./cm8d.exe
rundl:
	./cm8d.out