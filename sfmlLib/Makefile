
NAME	= sfml.so

CLANG 	= clang++

NCUR 	= -dynamiclib

FLAG	= -std=c++11 -Wall -Wextra -Werror

LIB		= SFML.class.hpp

SRC		= ../objects/Game.class.cpp\
		../objects/Snake.class.cpp\
		../objects/Unit.class.cpp\
		../objects/Food.class.cpp\
		../objects/Score_Time.class.cpp\
		../objects/Logic.class.cpp\
		SFML.class.cpp
		
OBJ		= $(SRC:.cpp=.o)

OBJ_DIR = ./objects/

SFML_DIR 	=	SFML_Lib/

SFML_LINK 	=	-F$(SFML_DIR)/SFML-2.5.0-macOS-clang/Frameworks -framework SFML -framework sfml-graphics -framework sfml-window -framework sfml-system
SFML_INC 	=	$(SFML_DIR)/SFML-2.5.0-macOS-clang/include
LIB_FLAG	=	-shared -rpath $(PWD)/$(SFML_FRM) -nostartfiles -dynamiclib

all: sfml $(NAME)

$(OBJ_DIR)%.o: %.cpp %.hpp
	@$(CLANG) $(FLAG) -c $< -o $@ -I../includes -I $(SFML_INC)

$(NAME): $(OBJ) $(LIB)
	@$(CLANG) $(FLAG)  $(OBJ) -o $(NAME) $(SFML_LINK) $(LIB_FLAG) -I $(SFML_INC)

sfml:
	@mkdir -p $(SFML_DIR)
	@test -d $(SFML_DIR)/SFML-2.5.0-macOS-clang || make sfml_dl

 sfml_dl:
	@curl -OL http://www.sfml-dev.org/files/SFML-2.5.0-macOS-clang.tar.gz
	@tar zxvfC 'SFML-2.5.0-macOS-clang.tar.gz' $(SFML_DIR)
	@rm -rf SFML-2.5.0-macOS-clang.tar.gz
	@cd $(SFML_DIR)/SFML-2.5.0-macOS-clang/Frameworks && ln -s ../extlibs/freetype.framework

clean:
	@rm -rf $(SFML_DIR)
	@rm -f *.o	

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all


# NAME 		=	sfml_lib.so

# CLANG++		=	clang++
# FLAGS 		=	-std=c++11 -Wall -Wextra -Werror -O3

# SFML_DIR 	=	SFML/
# SFML_INC 	=	$(SFML_DIR)/SFML-2.5.0-macOS-clang/include
# SFML_FRM	=	$(SFML_DIR)/SFML-2.5.0-macOS-clang/Frameworks
# SFML_LINK 	=	-F$(SFML_FRM) -framework SFML -framework sfml-graphics -framework sfml-window -framework sfml-system

# PWD 		=	$(shell pwd)
# LIB_FLAG	=	-shared -rpath $(PWD)/$(SFML_FRM) -nostartfiles -dynamiclib

# SRC_FILES	=	../srcs/Border.cpp \
# 				../srcs/Fruit.cpp  \
# 				../srcs/Init.cpp   \
# 				../srcs/Game.cpp   \
# 				../srcs/Logic.cpp  \
# 				../srcs/main.cpp   \
# 				../srcs/Score.cpp  \
# 				../srcs/Snake.cpp  \
# 				IGraphicsSFML.cpp

# INC_FILES	=	IGraphicsSFML.hpp

# INC_DIR		=	../includes

# OBJ_FILES 	=	$(SRC_FILES:.cpp=.cpp.o)

# all: sfml $(NAME)

# $(NAME): $(OBJ_FILES)
# 	@ $(CLANG++) $(FLAGS) -o $@ $(OBJ_FILES) $(SFML_LINK) $(LIB_FLAG) -I $(SFML_INC)

# %.cpp.o:%.cpp
# 	@ $(CLANG++) $(FLAGS) -c -o $@ $< -I $(INC_DIR) -I $(SFML_INC)

# sfml_dl:
# 	echo "\033[32m... loading SFML\033[39m"
# 	curl -OL http://www.sfml-dev.org/files/SFML-2.5.0-macOS-clang.tar.gz
# 	tar zxvfC 'SFML-2.5.0-macOS-clang.tar.gz' $(SFML_DIR)
# 	rm -rf SFML-2.5.0-macOS-clang.tar.gz
# 	cd $(SFML_FRM) && ln -s ../extlibs/freetype.framework

# sfml:
# 	mkdir -p $(SFML_DIR)
# 	test -d SFML/SFML-2.5.0-macOS-clang && echo "$(YELLOW)File SFML already exist$(RESET)" || make sfml_dl

# clean:
# 	@ rm -rf $(OBJ_FILES)
# 	@ rm -rf $(SFML_DIR)
# 	@ echo "\033[33mcleaned (SFML)\033[39m"

# fclean: clean
# 	@ rm -rf $(NAME)
# 	@ echo "\033[33mcleaned all (SFML)\033[39m"

# re: fclean all