NAME := test.sh

all:
	$(MAKE) -C ../ re
	cp ../pipex .
	./$(NAME)

clean:
	$(RM) -r output/
	$(RM) infile fn_used

fclean: clean
	$(MAKE) -C ../ fclean
	$(RM) pipex

re: fclean all
