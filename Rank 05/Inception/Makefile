all:
	mkdir -p $(HOME)/data/db $(HOME)/data/wp
	docker compose -f ./srcs/docker-compose.yml up -d --build

down:
	rm -rf /home/$(USER)/data/db /home/$(USER)/data/wp
	docker compose -f ./srcs/docker-compose.yml down

clean: down
	docker system prune -a

fclean: clean
	sudo rm -rf /home/$(USER)/data

re: fclean all

.PHONY: all down clean fclean re
