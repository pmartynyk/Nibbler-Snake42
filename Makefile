
NAME	= nibbler

CLANG = clang++

NCUR 	= -lncurses

FLAG	= -std=c++11 -Wall -Wextra -Werror 

LIB	= Game.class.hpp\
		IDynamiclibrary.hpp\
		Snake.class.hpp\
		Unit.class.hpp

SRC		= main.cpp\
		Game.class.cpp\
		Snake.class.cpp\
		Unit.class.cpp
		
OBJ		= $(SRC:.cpp=.o)

LIBS_DIR = ./includes/

SRC_DIR = ./src/

OBJ_DIR = ./objects/

SRCF = $(addprefix $(SRC_DIR), $(SRC))
LIBF = $(addprefix $(LIBS_DIR), $(LIBS))
OBJF = $(addprefix $(OBJ_DIR), $(OBJ))

all: mkdir $(NAME)

mkdir:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp 
	@$(CLANG) $(FLAG) -c $< -o $@ -I$(LIBS_DIR)

$(NAME): $(OBJF) $(LIBF) ncur 
	@$(CLANG) $(FLAG) $(OBJF) -o $(NAME) 
	@echo "\033[32mDONE\033[39m"

ncur:
	@make -C ./ncurses/
	@echo "\033[32mNcurses Builded\033[39m"

clean:
	@rm -f $(OBJ_DIR)*.o
	@rm -f $(SRC_DIR)*.o
	@rm -rf $(OBJ_DIR)
	@make -C ncurses clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ncurses fclean
	@echo "\033[32mCLEANED ALL\033[39m"

re: fclean all
