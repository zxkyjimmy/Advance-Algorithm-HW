ARCH = -march=native
FLAG = -O3 -std=c++17 -Wall
LINK =
CXXFLAGS = $(ARCH) $(FLAG)

SRCS = $(wildcard *.cc)

SUF = out
ifeq ($(OS), Windows_NT)
LINK += -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
SUF = exe
endif

EXEC = $(patsubst %.cc, %.$(SUF), $(SRCS))

all: $(EXEC)
$(EXEC): %.$(SUF): %.o
	$(CXX) -o $@ $< $(LINK)

.PHONY: clean clear
clean: clear
	rm -rf $(EXEC)
clear:
	rm -rf *.o
