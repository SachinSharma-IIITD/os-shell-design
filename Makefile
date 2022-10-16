all:
	@ gcc src/ls.c -o bin/ls
	@ gcc src/rm.c -o bin/rm
	@ gcc src/mkdir.c -o bin/mkdir
	@ gcc src/date.c -o bin/date
	@ gcc src/cat.c -o bin/cat
	@ gcc src/shell.c -o bin/shell
	@ bin/shell

clean:
	@ rm bin/ls bin/rm bin/mkdir bin/date bin/cat bin/shell

