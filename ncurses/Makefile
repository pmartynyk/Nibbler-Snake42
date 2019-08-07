
NAME	= ncurses.so

CLANG 	= clang++

NCUR 	= -dynamiclib -lncurses

FLAG	= -std=c++11 -Wall -Wextra -Werror

LIB		= Ncurses.class.hpp

SRC		= ../src/Game.class.cpp\
		../src/Snake.class.cpp\
		../src/Unit.class.cpp\
		Ncurses.class.cpp
		
OBJ		= $(SRC:.cpp=.o)

all: $(NAME)

$(OBJ_DIR)%.o: %.cpp 
	@$(CLANG) $(FLAG) -c $< -o $@ -I../includes

$(NAME): $(OBJ) $(LIB)
	@$(CLANG) $(FLAG) $(NCUR) $(OBJ) -o $(NAME) 

clean:
	@rm -f *.o	

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
