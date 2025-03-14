##
## PPROJECT, 2025
## Textris
## File description:
## void;
##

SRC  = $(shell find -iname *.c)
NAME = Textris

compile:
	@ gcc -g -Wall -Wextra $(SRC) $(LIBS) \
		-o $(NAME)

run: compile
	@ ./$(NAME)
	@ rm $(NAME)

valgrind: compile
	@valgrind -s --show-leak-kinds=none \
		--track-origins=yes \
		--leak-check=full \
		--error-limit=no \
	./$(NAME)
	@ rm $(NAME)

clean:
	@ rm -fr *.o

fclean: clean
	@ rm -f $(NAME)

re: fclean compile

kronk:
	@ echo "Oh ouais."
