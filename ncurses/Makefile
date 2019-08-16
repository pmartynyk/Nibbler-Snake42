
NAME	= ncurses.so

CLANG 	= clang++

NCUR 	= -dynamiclib -lncurses

FLAG	= -std=c++11 -Wall -Wextra -Werror

LIB		= Ncurses.class.hpp

SRC		= ../objects/Game.class.cpp\
		../objects/Snake.class.cpp\
		../objects/Unit.class.cpp\
		../objects/Food.class.cpp\
		../objects/Score_Time.class.cpp\
		../objects/Logic.class.cpp\
		Ncurses.class.cpp
		
OBJ		= $(SRC:.cpp=.o)

OBJ_DIR = ./objects/

all: $(NAME)
	@:
	
$(OBJ_DIR)%.o: %.cpp %.hpp
	@$(CLANG) $(FLAG) -c $< -o $@ -I../includes

$(NAME): $(OBJ) $(LIB)
	@$(CLANG) $(FLAG) $(NCUR) $(OBJ) -o $(NAME) 

clean:
	@rm -f *.o	

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
