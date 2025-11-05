NAME = inception

DATA_PATH = /home/mstasiak/data

all:
	@mkdir -p $(DATA_PATH)/wordpress
	@mkdir -p $(DATA_PATH)/mariadb
	@docker-compose -f srcs/docker-compose.yml up -d --build

down:
	@docker-compose -f srcs/docker-compose.yml down

stop:
	@docker-compose -f srcs/docker-compose.yml stop

start:
	@docker-compose -f srcs/docker-compose.yml start

clean: down
	@docker system prune -af

fclean: clean
	@sudo rm -rf $(DATA_PATH)/wordpress
	@sudo rm -rf $(DATA_PATH)/mariadb
	@docker volume rm srcs_wordpress srcs_mariadb 2>/dev/null || true

re: fclean all

.PHONY: all down stop start clean fclean re
