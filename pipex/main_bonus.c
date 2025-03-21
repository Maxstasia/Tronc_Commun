/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/21 15:19:29 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex_bonus.h"

static int child_process(t_pipex *pipex)
{
    int file;

    if (pipex->is_first)
    {
        file = open(pipex->filein, O_RDONLY);
        if (file < 0 && !pipex->here_doc)
            return(error(), 1);
        if (pipex->here_doc)
        {
            if (pipex->prev_fd == -1)
            {
                ft_putstr_fd("Error: Invalid prev_fd for here_doc\n", 2);
                exit(1);
            }
            if (dup2(pipex->prev_fd, STDIN_FILENO) == -1)
                perror("dup2 file to stdin failed");
            close(pipex->prev_fd); // Ferme après redirection
        }
        else if (file >= 0)
        {
            if (dup2(file, STDIN_FILENO) == -1)
                perror("dup2 file to stdin failed");
            close(file);
        }
    }
    else
    {
        if (pipex->prev_fd == -1)
        {
            ft_putstr_fd("Error: Invalid prev_fd\n", 2);
            exit(1);
        }
        if (dup2(pipex->prev_fd, STDIN_FILENO) == -1)
            perror("dup2 prev_fd to stdin failed");
    }
    if (!pipex->is_last)
    {
        if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
            perror("dup2 fd[1] to stdout failed");
    }
    else
    {
        file = open(pipex->fileout, O_WRONLY | O_CREAT | (pipex->here_doc ? O_APPEND : O_TRUNC), 0644);
        if (file < 0)
            return(error(), 1);
        if (dup2(file, STDOUT_FILENO) == -1)
            perror("dup2 file to stdout failed");
        close(file);
    }
    close(pipex->fd[0]);
    close(pipex->fd[1]);
    execute(pipex);
    return (0);
}

static void handle_here_doc(t_pipex *pipex)
{
    char *line;
    int fd[2];
    size_t delim_len;

    if (pipe(fd) < 0)
        error();
    delim_len = ft_strlen(pipex->argv[2]);
    while (1)
    {
        ft_putstr_fd("pipex heredoc> ", 1);
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break ;
        if (ft_strncmp(line, pipex->argv[2], delim_len) == 0 && line[delim_len] == '\n')
            break ;
        ft_putstr_fd(line, fd[1]);
        free(line);
    }
    free(line);
    close(fd[1]);
    pipex->prev_fd = fd[0];
}

static pid_t fork_process(t_pipex *pipex, int i, int cmd_count)
{
    pid_t pid;

    ft_putstr_fd("Debug: Creating pipe for process ", 2);
    ft_putnbr_fd(i, 2);
    ft_putstr_fd("\n", 2);
    if (pipe(pipex->fd) < 0)
        error();
    ft_putstr_fd("Debug: Pipe created, fd[0] = ", 2);
    ft_putnbr_fd(pipex->fd[0], 2);
    ft_putstr_fd(", fd[1] = ", 2);
    ft_putnbr_fd(pipex->fd[1], 2);
    ft_putstr_fd("\n", 2);
    pid = fork();
    if (pid < 0)
        error();
    if (pid == 0)
    {
        pipex->is_first = (i == 0);
        pipex->is_last = (i == cmd_count - 1);
        pipex->argv = &pipex->argv[i + 2];
        ft_putstr_fd("Debug: Child process starting for cmd: ", 2);
        ft_putstr_fd(pipex->argv[0], 2);
        ft_putstr_fd("\n", 2);
        child_process(pipex);
        exit(0);
    }
    if (pipex->prev_fd != -1)
        close(pipex->prev_fd);
    pipex->prev_fd = pipex->fd[0];
    close(pipex->fd[1]);
    return (pid);
}

int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;
    int i, cmd_count, status, last_status = 0;
    pid_t last_pid;

    if (argc < 5)
        usage();
    pipex.argv = argv;
    pipex.envp = envp;
    pipex.here_doc = (ft_strcmp(argv[1], "here_doc") == 0);
    pipex.filein = argv[1], pipex.fileout = argv[argc - 1], pipex.prev_fd = -1;
    cmd_count = argc - (pipex.here_doc ? 4 : 3);
    ft_putstr_fd("Debug: Before handle_here_doc\n", 2);
    if (pipex.here_doc)
        handle_here_doc(&pipex);
    else
        pipex.prev_fd = open(pipex.filein, O_RDONLY);
    ft_putstr_fd("Debug: After handle_here_doc, prev_fd = ", 2);
    ft_putnbr_fd(pipex.prev_fd, 2);
    ft_putstr_fd("\n", 2);
    ft_putstr_fd("Debug: Checking pipex->fd before fork, fd[0] = ", 2);
    ft_putnbr_fd(pipex.fd[0], 2); // Test d'accès à fd[0]
    ft_putstr_fd(", fd[1] = ", 2);
    ft_putnbr_fd(pipex.fd[1], 2); // Test d'accès à fd[1]
    ft_putstr_fd("\n", 2);
    i = -1;
    while (++i < cmd_count)
    {
        ft_putstr_fd("Debug: Forking process ", 2);
        ft_putnbr_fd(i, 2);
        ft_putstr_fd("\n", 2);
        last_pid = fork_process(&pipex, i, cmd_count);
    }
    if (pipex.prev_fd != -1)
        close(pipex.prev_fd);
    while (wait(NULL) > 0 && errno != ECHILD)
        ;
    waitpid(last_pid, &status, 0);
    if (WIFEXITED(status))
        last_status = WEXITSTATUS(status);
    return (last_status);
}
