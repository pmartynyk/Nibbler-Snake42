NAME 		=	SDLlib.so

COM			=	clang++
FLAGS		=	-std=c++11 -O3 -Wall -Wextra -Werror 

SDL_DIR		=	./SDL
SDL_FRM		=	-F $(SDL_DIR)
SDL_LINK	=	-framework SDL2 -framework SDL2_ttf

PWD			= 	$(shell pwd)
LIB_FLAG	=	-shared  -rpath $(PWD)/$(SDL_DIR) -nostartfiles -dynamiclib

SRC_FILES	=	SDLlib.class.cpp \
		../objects/Game.class.cpp\
		../objects/Snake.class.cpp\
		../objects/Unit.class.cpp\
		../objects/Food.class.cpp\
		../objects/Score_Time.class.cpp\
		../objects/Logic.class.cpp\

INC_FILES	=	SDLlib.class.hpp

INC_DIR		=	../includes

OBJ_FILES	= 	$(SRC_FILES:.cpp=.o)

SDL2 		=	SDL2

all: sdl $(NAME)
	@:
	
$(NAME): $(OBJ_FILES)
	@ $(COM) $(FLAGS) $(SDL_FRM) $(SDL_LINK) $(LIB_FLAG) $(OBJ_FILES) -o $(NAME)

%.o:%.cpp %.hpp
	@ $(COM) $(FLAGS) $(SDL_FRM) -c $< -o $@  -I $(INC_DIR)

sdl:
	@ mkdir -p $(SDL_DIR)
	@ test -f SDL/SDL2.framework/SDL2 || make sdl2_download
	@ test -f SDL/SDL2_ttf.framework/SDL2_ttf || make sdl_ttf_download

sdl2_download:
	@ curl -o sdl2.dmg https://www.libsdl.org/release/SDL2-2.0.9.dmg
	@ hdiutil attach sdl2.dmg;
	@ cd ; cp -R -i ../../../Volumes/SDL2/SDL2.framework $(PWD)/$(SDL_DIR)/SDL2.framework; hdiutil eject ../../../Volumes/SDL2;
	@ rm -rf sdl2.dmg

sdl_ttf_download:
	@ curl -o sdl_ttf.dmg https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.dmg
	@ hdiutil attach sdl_ttf.dmg;
	@ cd ; cp -R -i ../../../Volumes/SDL2_ttf/SDL2_ttf.framework $(PWD)/$(SDL_DIR)/SDL2_ttf.framework; hdiutil eject ../../../Volumes/SDL2_ttf;
	@ rm -rf sdl_ttf.dmg

clean:
	@ rm -rf $(OBJ_FILES)
	@ rm -rf $(SDL_DIR)

fclean:	clean
	@ rm -rf $(NAME)
	
re:	fclean all

.PHONY: all sdl clean fclean re