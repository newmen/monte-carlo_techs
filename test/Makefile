CXX = g++
CXX_CFLAGS = -Wall -O3 -std=c++0x
LIBS = ../*.o
NAME = test_mc

default:	$(NAME)

$(NAME):
	$(CXX) $(CXX_CFLAGS) $(LIBS) *.cpp -o $(NAME)

clean:
	rm $(NAME)
