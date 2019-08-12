# NAME = SDLlib.so

# FLAGS = -std=c++11 #-Wall -Wextra -Werror

# CLANG 	= clang++

# DYNAMIC_LIB = -dynamiclib

# HDR = SDLlib.class.hpp

# SRC =	SDLlib.class.cpp \
# 		../objects/Game.class.cpp\
# 		../objects/Snake.class.cpp\
# 		../objects/Unit.class.cpp\
# 		../objects/Food.class.cpp\
# 		../objects/Score_Time.class.cpp\
# 		../objects/Logic.class.cpp\

# OBJ =	$(SRC:.cpp=.o)

# INCLUDES =	-I./frameworks/SDL2.framework/Headers/ \
# 			-I./frameworks/SDL2_image.framework/Headers/ \
# 			-I./frameworks/SDL2_mixer.framework/Headers/ \
# 			-I./frameworks/SDL2_ttf.framework/Headers/ \
# 			-I../includes

# FRAMEWORKS = -F./frameworks -rpath ./frameworks -framework SDL2 \
# 												-framework SDL2_image \
# 												-framework SDL2_mixer \
# 												-framework SDL2_ttf

# all: $(NAME)

# $(OBJ_DIR)%.o:	%.cpp %.hpp
# 	@$(CLANG) $(FLAGS) -c $< -o $@ $(FRAMEWORKS) $(INCLUDES) 

# $(NAME): $(OBJ) $(HDR)
# 	@$(CLANG) $(FLAGS) $(DYNAMIC_LIB) $(OBJ) -o $(NAME) 

# clean:
# 	@rm -f *.o	

# fclean: clean
# 	@rm -f $(NAME)

# re: fclean all

# -----------------------------
NAME 		=	SDLlib.so

COM			=	clang++
FLAGS		=	-std=c++11 -O3 #-Wall -Wextra -Werror 

SDL_DIR		=	./SDL
SDL_FRM		=	-F $(SDL_DIR)
SDL_LINK	=	-framework SDL2

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

$(NAME): $(OBJ_FILES)
	@ $(COM) $(FLAGS) $(SDL_FRM) $(SDL_LINK) $(LIB_FLAG) $(OBJ_FILES) -o $(NAME)

%.cpp.o:%.cpp %.hpp
	@ $(COM) $(FLAGS) $(SDL_FRM) -c -o $@ $< -I $(INC_DIR)


sdl:
	@ mkdir -p $(SDL_DIR)
	@ test -f SDL/SDL2.framework/SDL2 && echo "\033[33mFile $(SDL2) already exist\033[39m" || make sdl2_download

sdl2_download:
	echo "\033[32m... loading SDL\033[39m"
	@ curl -o sdl2.dmg https://www.libsdl.org/release/SDL2-2.0.8.dmg
	@ hdiutil attach sdl2.dmg;
	@ cd ; cp -R -i ../../../Volumes/SDL2/SDL2.framework $(PWD)/$(SDL_DIR)/SDL2.framework; hdiutil eject ../../../Volumes/SDL2;
	@ rm -rf sdl2.dmg

clean:
	@ rm -rf $(OBJ_FILES)
	@ rm -fr $(SDL_DIR)
	@ echo "\033[33mcleaned (SDL)\033[39m"

fclean:	clean
	@ rm -rf $(NAME)
	@ echo "\033[33mcleaned all (SDL)\033[39m"
	
re:	fclean all

.PHONY: all sdl clean fclean re