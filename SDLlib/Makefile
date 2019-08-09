NAME = SDLlib.so

FLAGS = -std=c++11 -Wall -Wextra -Werror

CLANG 	= clang++

OBJ_DIR = ./obj/
SRC_DIR = ./src/
INCDIR = ./inc/

SRC =	main.cpp \
		SDLlib.class.cpp \

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))
HDRS = -I $(INCDIR)

INCLUDES =	-I./frameworks/SDL2.framework/Headers/ 

FRAMEWORKS = -F./frameworks -rpath ./frameworks -framework SDL2 

all: $(NAME)

$(NAME): $(OBJ)
		$(CLANG) $(FLAGS) $(OBJ) -o $(NAME) $(HDRS) $(FRAMEWORKS)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
		@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
				$(CLANG) -c $< -o $@ $(FLAGS) $(HDRS) $(INCLUDES)

clean:
	@rm -f $(OBJ)

fclean: clean
		@rm -f $(NAME)
		@rm -rf $(OBJ_DIR)

re: fclean all