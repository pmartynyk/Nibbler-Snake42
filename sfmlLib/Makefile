NAME	= sfml.so

CLANG 	= clang++

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


SFML_DIR 	=	SFML_Lib/
SFML_INC 	=	SFML_Lib/SFML-2.5.0-macOS-clang/include
SFML_FRM	=	SFML_Lib/SFML-2.5.0-macOS-clang/Frameworks
SFML_LINK 	=	-F$(SFML_FRM) -framework SFML -framework sfml-graphics -framework sfml-window -framework sfml-system

PWD 		=	$(shell pwd)
LIB_FLAG	=	-shared -rpath $(PWD)/$(SFML_FRM) -nostartfiles -dynamiclib

all: sfml $(NAME)

%.o:%.cpp
	@$(CLANG) $(FLAG) -c $< -o $@ -I../includes -I$(SFML_INC)

$(NAME): $(OBJ)
	@$(CLANG) $(FLAG) $(OBJ) -o $(NAME) $(SFML_LINK) $(LIB_FLAG) -I$(SFML_INC)

sfml:
	@mkdir -p $(SFML_DIR)
	@test -d SFML_Lib/SFML-2.5.0-macOS-clang || make sfml_dl

 sfml_dl:
	@curl -OL http://www.sfml-dev.org/files/SFML-2.5.0-macOS-clang.tar.gz
	@tar zxvfC 'SFML-2.5.0-macOS-clang.tar.gz' $(SFML_DIR)
	@rm -rf SFML-2.5.0-macOS-clang.tar.gz
	@cd SFML_Lib/SFML-2.5.0-macOS-clang/Frameworks && ln -s ../extlibs/freetype.framework

clean:
	@rm -rf $(SFML_DIR)
	@rm -f *.o	

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all