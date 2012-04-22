CPP=g++
CPPFLAGS=-I../libMLcourse/src -ffast-math -Wall -Wextra -Werror -pedantic-errors
LDFLAGS=-L../libMLcourse/lib -lMLcourse

all: ueb2

.PHONY: ueb2

ueb2: 
	$(CPP) $(CPPFLAGS) $(LDFLAGS) src/*.cpp -o ueb2

clean:
	rm ueb2

