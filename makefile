#Makefile

OBJS = main.o minesweeper.o msboardtextview.o mssfmlview.o mstextcontroller.o
CXX = clang++
CXXFLAGS = -Wall -std=c++11
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

MS: $(OBJS)
	$(CXX) -o MS $(OBJS) $(LDLIBS) $(LDFLAGS)

clean:
	$(RM) MS $(OBJS)
