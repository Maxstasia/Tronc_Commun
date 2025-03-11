NAME := test.sh

all:
	$(MAKE) -C ../ re_bonus
	cp ../pipex_bonus .
	./$(NAME)

clean:
	$(RM) -r output/
	$(RM) infile fn_used

fclean: clean
	$(MAKE) -C ../ fclean
	$(RM) pipex

re: fclean all
