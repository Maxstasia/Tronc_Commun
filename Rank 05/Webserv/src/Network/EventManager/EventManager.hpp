#pragma once

#include "FileUtils.hpp"
#include <sys/epoll.h>

class EventManager
{
  private:
	int _epoll_fd;
	struct epoll_event _ev;

  public:
	EventManager();
	~EventManager();

	void initialize();
	void addFd(int fd, uint32_t events);
	void modifyFd(int fd, uint32_t events);
	void removeFd(int fd);
	int waitEvents(struct epoll_event* events, int max_events, int timeout);
	int getEpollFd() const;
	void cleanup();
};
