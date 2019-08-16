
NAME	= music.so

CLANG 	= clang++

NCUR 	= -dynamiclib

FLAG	= -std=c++11 -Wall -Wextra -Werror

LIB		= Music.class.hpp

SRC		= Music.class.cpp
		
OBJ		= $(SRC:.cpp=.o)

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
