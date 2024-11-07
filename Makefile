multiple_system_launcher: multiple_system_launcher.c launcher
	gcc multiple_system_launcher.c -o multiple_system_launcher
launcher: launcher.c brain ear mouth
	gcc launcher.c -o launcher
brain: brain.c
	gcc brain.c -o brain
ear: ear.c
	gcc ear.c -o ear
mouth: mouth.c
	gcc mouth.c -o mouth
clean:
	rm -rf *.txt launcher brain ear mouth multiple_system_launcher