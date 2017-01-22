obj_dir=obj/
bin_dir=bin/
src_dir=src/
CC=gcc
CFLAGS=-Wall -lSDL2_image -lSDL2 
LDFLAGS=`sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_gfx
EXEC=$(bin_dir)GSA.exe

all: $(EXEC)

$(bin_dir)GSA.exe: $(obj_dir)BDD.o $(obj_dir)Camera.o $(obj_dir)Couleur.o $(obj_dir)ImageBMP.o $(obj_dir)ReconnaissanceV.o $(obj_dir)Sdl_fenetres.o $(obj_dir)Sdl_init.o $(obj_dir)Sdl_main.o $(obj_dir)Stock.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(obj_dir)%.o: $(src_dir)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

doxygen:
	doxygen Doxyfile

clean:
	rm -f $(obj_dir)* $(bin_dir)*

start:
	./bin/GSA.exe

forceMaj:
	git pull &&	make clean && make && make start
	
maj:
	git pull && make && make start

