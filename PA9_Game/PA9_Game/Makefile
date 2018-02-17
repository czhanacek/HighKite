LIBS=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
OUTPUT=highkite

all: 
	@echo "** Building the game **"
	g++ *.cpp -o $(OUTPUT) $(LIBS)

install:
	@echo "** Installing the game **"
	cp $(OUTPUT) /usr/bin/$(OUTPUT)

uninstall:
	@echo "** Uninstalling the game **"
	rm /usr/bin/$(OUTPUT)
