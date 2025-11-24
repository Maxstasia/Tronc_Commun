NAME		= inception
DOMAIN		= mstasiak.42.fr

all: hosts volumes
	@docker compose -f ./srcs/docker-compose.yml up -d --build

down:
	@sudo rm -rf /home/$(USER)/data/db /home/$(USER)/data/wordpress
	@docker compose -f ./srcs/docker-compose.yml down

clean: down
	@docker system prune -a --volumes -f

fclean: clean remove_hosts
	@sudo rm -rf /home/$(USER)/data
	@sudo rm -rf ./srcs/requirements/wordpress/wp-content

re: fclean all

volumes:
	@mkdir -p /home/$(USER)/data/db
	@mkdir -p /home/$(USER)/data/wordpress

hosts:
	@if ! grep -q "$(DOMAIN)" /etc/hosts; then \
		echo "127.0.0.1	$(DOMAIN)" | sudo tee -a /etc/hosts > /dev/null; \
		echo "✅ Added $(DOMAIN) to /etc/hosts"; \
	else \
		echo "✅ $(DOMAIN) already in /etc/hosts"; \
	fi

remove_hosts:
	@sudo sed -i '/$(DOMAIN)/d' /etc/hosts
	@echo "🗑️  Removed $(DOMAIN) from /etc/hosts"

.PHONY: all down clean fclean re volumes hosts remove_hosts
