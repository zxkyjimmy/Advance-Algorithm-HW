ARCHS = -march=native
FLAGS = -std=c++17 -Wall -O3
LINKS =
SRCS = $(wildcard *.cc)
ifeq ($(OS), Windows_NT)
EXTENSION = exe
LINKS += -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
else
EXTENSION = out
endif
EXEC = $(patsubst %.cc, %.$(EXTENSION), $(SRCS))
all: $(EXEC)
%.$(EXTENSION): %.cc
	g++ -o $@ $< $(ARCHS) $(FLAGS) $(LINKS)
.PHONY: clean
clean:
	@rm -rf $(EXEC) output.txt