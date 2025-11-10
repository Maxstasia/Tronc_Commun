NAME		= inception

all: volumes
	@docker compose -f ./srcs/docker-compose.yml up -d --build

down:
	@sudo rm -rf /home/$(USER)/data/db /home/$(USER)/data/wp
	@docker compose -f ./srcs/docker-compose.yml down

clean: down
	@docker system prune -a --volumes -f

fclean: clean
	@sudo rm -rf /home/$(USER)/data

re: fclean all

volumes:
	@mkdir -p /home/$(USER)/data/db
	@mkdir -p /home/$(USER)/data/wp

.PHONY: all down clean fclean re volumes
