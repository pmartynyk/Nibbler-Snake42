
NAME	= nibbler

CLANG = clang++

NCUR 	= -lncurses

FLAG	= -std=c++11 -Wall -Wextra -Werror 

LIB	= Game.class.hpp\
		IDynamiclibrary.hpp\
		Snake.class.hpp\
		Unit.class.hpp\
		Food.class.hpp\
		Score_Time.class.hpp\
		Logic.class.hpp

SRC		= main.cpp\
		Game.class.cpp\
		Snake.class.cpp\
		Unit.class.cpp\
		Food.class.cpp\
		Score_Time.class.cpp\
		Logic.class.cpp
		
OBJ		= $(SRC:.cpp=.o)

LIBS_DIR = ./includes/

SRC_DIR = ./src/

OBJ_DIR = ./objects/

SRCF = $(addprefix $(SRC_DIR), $(SRC))
LIBF = $(addprefix $(LIBS_DIR), $(LIB))
OBJF = $(addprefix $(OBJ_DIR), $(OBJ))

all: mkdir $(NAME)
	@:
	
mkdir:
	@mkdir -p $(OBJ_DIR)


$(NAME): $(OBJF) $(LIBF) ncur sdl sfml mus
	@$(CLANG) $(FLAG) $(OBJF) -o $(NAME) 
	@echo "\033[32mDONE\033[39m"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp #$(LIBS_DIR)%.hpp
	@$(CLANG) $(FLAG) -c $< -o $@ -I$(LIBS_DIR)

mus:
	@make -C ./music/
	@echo "\033[32mMusic Builded\033[39m"

ncur:
	@make -C ./ncurses/
	@echo "\033[32mNcurses Builded\033[39m"

sdl:
	@make -C ./SDLlib/
	@echo "\033[32mSDL Builded\033[39m"

sfml:
	@make -C ./sfmlLib/
	@echo "\033[32mSFML Builded\033[39m"

clean:
	@rm -f $(OBJ_DIR)*.o
	@rm -f $(SRC_DIR)*.o
	@rm -rf $(OBJ_DIR)
	@make -C music clean
	@make -C ncurses clean
	@make -C SDLlib clean
	@make -C sfmlLib clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C music fclean
	@make -C ncurses fclean
	@make -C SDLlib fclean
	@make -C sfmlLib fclean
	@echo "\033[32mCLEANED ALL\033[39m"

re: fclean all
