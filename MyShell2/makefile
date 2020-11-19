cc = gcc
prom = shell
obj = main.o welcomeScreen.o shellPrompt.o commandHandler.o

$(prom):$(obj)
	$(cc)  -lreadline  -o $(prom)  $(obj)

main.o: main.c $(deps)
	$(cc) -c  -lreadline main.c

welcomeScreen.o :welcomeScreen.c $(deps)
	$(cc) -c welcomeScreen.c

shellPrompt.o :shellPrompt.c $(deps)
	$(cc) -c shellPrompt.c

commandHandler.o :commandHandler.c $(deps)
	$(cc) -c commandHandler.c