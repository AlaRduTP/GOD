HEADERS = game/coord.h game/zone.h game/drone.h game/iter.h game/game.h
FILES = game/coord.cpp game/zone.cpp game/drone.cpp game/game.cpp main.cpp

all:
	g++ -std=c++17 $(FILES)

happy:
	@./happy.sh $(HEADERS) $(FILES)
	g++ -std=c++17 happy.cpp

clean:
	rm a.out
