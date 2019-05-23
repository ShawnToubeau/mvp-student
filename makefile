all: program1

program1: mvp-student.c
	gcc -o mvp-student.x mvp-student.c

clean:
	rm *.x