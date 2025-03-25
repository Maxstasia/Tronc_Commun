/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstasiak <mstasiak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:35:53 by mstasiak          #+#    #+#             */
/*   Updated: 2025/03/25 16:07:32 by mstasiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex_bonus.h"

static void	init_pipex(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->here_doc = (ft_strcmp(argv[1], "here_doc") == 0);
	pipex->filein = argv[1];
	pipex->fileout = argv[argc - 1];
	pipex->prev_fd = -1;
}

static void launch_processes(t_pipex *pipex, t_temp *tmp)
{
    int i;

    i = -1;
    tmp->last_pid = -1;
    while (++i < tmp->cmd_count)
        tmp->last_pid = fork_process(pipex, i, tmp);
    if (pipex->prev_fd != -1)
        close(pipex->prev_fd);
    while (wait(NULL) > 0 && errno != ECHILD)
        ;
    if (tmp->last_pid > 0)
    {
        tmp->status = 0;
        if (waitpid(tmp->last_pid, &tmp->status, 0) > 0 && WIFEXITED(tmp->status))
            tmp->last_status = WEXITSTATUS(tmp->status);
        else
            tmp->last_status = 1;
    }
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	t_temp	tmp;

	if (argc < 5 || (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6))
		usage();
	tmp.last_status = 0;
	tmp.status = 0;
	init_pipex(&pipex, argc, argv, envp);
	if (pipex.here_doc)
	{
		handle_here_doc(&pipex);
		tmp.cmd_count = argc - 4;
	}
	else
		tmp.cmd_count = argc - 3;
	launch_processes(&pipex, &tmp);
	return (tmp.last_status);
}
