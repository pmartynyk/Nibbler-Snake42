
NAME	= nibbler

CLANG = clang++ -std=c++11

FLAG	= -Wall -Wextra -Werror

LIB	= Game.class.hpp

SRC		= main.cpp\
		Game.class.cpp

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

$(NAME): $(OBJF) $(LIBF)
	@$(CLANG) $(FLAG) $(OBJF) -o $(NAME) 
	@echo "\033[32mDONE\032"

clean:
	@rm -f $(OBJ_DIR)*.o
	@rm -rf $(OBJ_DIR)

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\033[32mCLEANED ALL\032"

re: fclean all