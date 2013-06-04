all:
ifeq ($(shell uname -s),Darwin)	
	gcc src/*.c src/logic/*.c src/engine/*.c src/utils/*.c  -o gridfire -lcsfml-graphics -lcsfml-window -lcsfml-network -lcsfml-system -lcsfml-audio -lm -g -ljnxc -pthread -F/Library/Frameworks -framework freetype
endif
	gcc src/*.c src/logic/*.c src/engine/*.c src/utils/*.c  -o gridfire -lcsfml-graphics -lcsfml-window -lcsfml-network -lcsfml-system -lcsfml-audio -lm -g -ljnxc -pthread -lX11
