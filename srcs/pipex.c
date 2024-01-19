/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:32:11 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/19 20:55:04 by tpotilli         ###   ########.fr       */
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

int	ft_pipex(char *argv[], char *env[], int argc)
{
	pid_t		pid[argc];
	int			**pipefd;
	int			i;

	i = 0;
	pipefd = NULL;
	pipefd = alloc_pipe(i, pipefd);
	if (!pipefd[1] || !pipefd[0])
		return (free(pipefd), -1);
	while (i < argc)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (printf("erreur de fork\n"), 1);
		if (pid[i] == 0)
		{
			if (i == 0)
			{
				if (child_process_in(pipefd, argv, env, i) == -1)
					return (free(pipefd[0]), free(pipefd[1]), free(pipefd), -1);
			}
			else if (i == argc - 1)
			{
				if (child_process_out(pipefd, argv, env, i) == -1)
					return (free(pipefd[0]), free(pipefd[1]), free(pipefd), -1);
			}
			else
			{
				if (child_process_middle(pipefd, argv, env, i) == -1)
					return (free(pipefd[0]), free(pipefd[1]), free(pipefd), -1);
			}
		}
		else
			pipefd = parent_process(pipefd, i);
		i++;
	}
	i = 0;
	while (i < argc)
	{
		// fprintf(stderr, "voici le pid qui attend %d\n", pid[i]);
		waitpid(pid[i], NULL, 0);
		i++;
	}
	// fprintf(stderr, "HELOOOOO\n");
	free(pipefd[0]);
	free(pipefd[1]);
	free(pipefd);
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
		pipe(pipefd[1]);
	}
	return (pipefd);
}

int	**parent_process(int **pipefd, int i)
{
	// fprintf(stderr, "je suis dans le parent et voici mon i %d\n", i);
	if (i % 2 == 0)
	{
		if (!pipefd[0] || !pipefd[1])
			return (free(pipefd[0]), free(pipefd[1]), free(pipefd), NULL);
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		pipe(pipefd[0]);
	}
	else
	{
		if (!pipefd[0] || !pipefd[1])
			return (free(pipefd[0]), free(pipefd[1]), free(pipefd), NULL);
		close(pipefd[1][1]);
		close(pipefd[1][0]);
		pipe(pipefd[1]);
	}
	// if (!pipefd[1] || !pipefd[0])
	// 	return (free(pipefd), NULL);
	return (pipefd);
}

// faire 2 pipe puis dans la boucle tu fork et si dans parent et j'en recree dans le parent
// faire attention au modulo
t_pipes *init_struct()
{
	t_pipes *pipes;
	int		i;

	i = 0;
	pipes = malloc(sizeof(t_pipes) * 2);
	if (!pipes)
		return (printf("problem malloc\n"), NULL);
	while (i < 2)
	{
		if (pipe(pipes[i].pipes) == -1)
			return (printf("pipe problem\n"), free(pipes), NULL);
		i++;
	}
	return (pipes);
}

/*
if (i % 2 == 0)
	{
		close(pipefd[0][0]);
		close(pipefd[0][1]);
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
		close(pipefd[1][0]);
		close(pipefd[1][1]);
		if (!pipefd[0] || !pipefd[1])
		{
			free(pipefd[0]);
			free(pipefd[1]);
			return (pipefd);
		}
		pipe(pipefd[0]);
	}
*/

	// if (pid > 0)
		// parent_process(pipefd);
	// int	j = 0;
	// int status = 0;
	// close(pipefd[0][0]);
	// close(pipefd[0][1]);
	// close(pipefd[1][0]);
	// close(pipefd[1][1]);
	// while (j < argc)
	// {
	// 	waitpid(pid[j], &status, 0);
	// 	j++;
	// }