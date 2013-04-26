all:
	gcc src/*.c src/engine/*.c src/utils/*.c  -o gridfire -lcsfml-graphics -lcsfml-window -lcsfml-network -lcsfml-system -lm -g -ljnxc
