/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:32:11 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/15 15:02:27 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**	This function takes as parameter: 
**
**	Char *argv
**	char *envp
**  int fd1
**  int fd4
**
** =====================================================
** =====================================================
**
** pid_t to stock the identifiers of process
** pipefd[2] tab to stock the identifiers of pid(reading or writing)
** status to verify the status at child
**
** pid1 = fork () call fork to creat a copy of the parent
** if fork work
** -> parent get the child identifiers in pid1
** if doesn't work -> return (1) 
**
** if pid is negative return 1, if pid1 == 0 child process
**
** waitpid() wait the end of parent to wait child
*/
// faire plusieurs pipe de maniere intelligente

int	ft_pipex(char *argv[],  char *env[], int argc)
{
	int			i;
	pid_t		pid;
	int			**pipefd;
	int			status;
	// pid_t		pid;
	// t_pipes		*pipesfd;

	status = 0;
	i = 0;
	while (i < argc)
	{
		pipefd = alloc_pipe(i, pipefd);
		if (!pipefd[1] || !pipefd[0])
			return (free(pipefd), -1);
		pid = fork();
		if (pid < 0)
			return (printf("erreur de fork\n"), 1);
		if (pid == 0)
		{
			if (i == 0)
				child_process_in(pipefd, argv, env, i);
			else if (i == argc - 1)
				child_process_out(pipefd, argv, env, i);
			else
				child_process_middle(pipefd, argv, env, i);
		}
		i++;
	}
	i = 0;
	fprintf(stderr, "HELOOOOO\n");
	// if (pid > 0)
	// {
	// 	fprintf(stderr, "je vais dans parent\n");
	// 	parent_process(pipefd, argv, i, pid);
	// }
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	close(pipefd[1][0]);
	close(pipefd[1][1]);
	free(pipefd);
	fprintf(stderr, "je suis juste avant un waitpid\n");
	waitpid(-1, &status, 0);
	return (0);
}

int	**alloc_pipe(int i, int **pipefd)
{
	if (i == 0)
	{
		pipefd = malloc(sizeof(int *) * 2);
		if (!pipefd)
			return (fprintf(stderr, "probleme happend in alloc_pipe"), NULL);
		pipefd[0] = malloc(sizeof(int) * 2);
		pipefd[1] = malloc(sizeof(int) * 2);
		if (!pipefd[0] || !pipefd[1])
		{
			free(pipefd[0]);
			free(pipefd[1]);
			return (pipefd);
		}
		pipe(pipefd[0]);
	}
	if (i % 2 == 0)
	{
		free(pipefd[0]);
		pipefd[0] = malloc(sizeof(int) * 2);
		if (!pipefd[0] || !pipefd[1])
		{
			free(pipefd[0]);
			free(pipefd[1]);
			return (pipefd);
		}
		pipe(pipefd[0]);
	}
	else
	{
		free(pipefd[1]);
		pipefd[1] = malloc(sizeof(int) * 2);
		if (!pipefd[0] || !pipefd[1])
		{
			free(pipefd[0]);
			free(pipefd[1]);
			return (pipefd);
		}
		pipe(pipefd[1]);
	}
	return (pipefd);
}

// int	parent_process(int **pipefd, char *argv[], int i, pid_t pid)
// {
// 	int			status;
// 	pid_t		pid_child;
// 	int			argc;


// 	argc = ft_strlen(argv[i]);
// 	status = 0;
// 	i = 0;
// 	fprintf(stderr, "je suis au wait\n");
// 	// if (pid[i] > 0)
// 	// {
// 	// 	close(pipefd[0][0]);
// 	// 	close(pipefd[0][1]);
// 	// 	close(pipefd[1][0]);
// 	// 	close(pipefd[1][1]);
// 	// }
// 	while (i < argc)
// 	{
// 		pid_child = waitpid(pid, &status, 0);
// 		if (pid_child == -1)
// 			return (printf("problem pid\n"), free(pipefd), -1);
// 		fprintf(stderr, "pid dans boucle = %d\n", pid);
// 		fprintf(stderr, "i dans ma boucle de pid %d\n", i);
// 	}
// 	return (0);
// }

// faire 2 pipe puis dans la boucle tu fork et si dans parent et j'en recree dans le parent
// faire attention au modulo
// t_pipes *init_struct()
// {
// 	t_pipes *pipes;
// 	int		i;

// 	i = 0;
// 	pipes = malloc(sizeof(t_pipes) * 2);
// 	if (!pipes)
// 		return (printf("problem malloc\n"), NULL);
// 	while (i < 2)
// 	{
// 		if (pipe(pipes[i].pipes) == -1)
// 			return (printf("pipe problem\n"), free(pipes), NULL);
// 		i++;
// 	}
// 	return (pipes);
// }
