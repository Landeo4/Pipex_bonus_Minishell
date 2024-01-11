/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:28:48 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/11 16:47:04 by tpotilli         ###   ########.fr       */
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
	pid_t		pid[2];
	int			status;
	pid_t		pid_child;
	int			**pipefd;
	// t_pipes		*pipesfd;

	i = 0;
	status = 0;
	(void)status;
	argc--;
	while (argv[i])
	{
		fprintf(stderr, "voici liste arg %s\n", argv[i]);
		i++;
	}
	fprintf(stderr, "voici argc %d\n", argc);
	// pipesfd = init_struct();
	i = 0;
	while (i < argc)
	{
		pipefd = alloc_pipe(i, pipefd);
		if (!pipefd[1] || !pipefd[0])
			return (free(pipefd), -1);
		pid[i] = fork();
		if (pid[i] < 0)
			return (printf("erreur de fork\n"), 1);
		if (pid[i] == 0)
		{
			// fprintf(stderr, "je vais de child process et pipe fd est %d\n", pipesfd[i] % 2);
			if (i == 0)
			{
				fprintf(stderr, "===je vais dans child_proces_in===\n");
				fprintf(stderr, "voici mes argument i %d et argv %s\n", i, argv[i]);
				child_process_in(pipefd, argv, env, i);
			}
			else if (i == argc - 1)
			{
				fprintf(stderr, "///je vais dans child_proces_OUT///\n");
				fprintf(stderr, "voici mes argument i %d et argv %s\n", i, argv[i]);
				child_process_out(pipefd, argv, env, i);
			}
			else
			{
				fprintf(stderr, "///je vais dans child_proces_pair///\n");
				fprintf(stderr, "voici mes argument i %d et argv %s\n", i, argv[i]);
				child_process_middle(pipefd, argv, env, i);
			}
		}
		// else if (pid[i] > 0)
		// {
		// 	fprintf(stderr, "je vais dans le parent\n");
		// 	parent_process(pipesfd, argv, env, i);
		// }
		i++;
	}
	i = 0;
	if (pid[i] > 0)
	{
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		close(pipefd[1][0]);
		close(pipefd[1][1]);
	}
	i = 0;
	fprintf(stderr, "je suis au wait\n");
	while (i < argc)
	{
		pid_child = waitpid(pid[i], &status, 0);
		if (pid_child == -1)
			return (printf("problem pid\n"), free(pipefd), -1);
		fprintf(stderr, "pid dans boucle = %d\n", pid[i]);
		fprintf(stderr, "i dans ma boucle de pid %d\n", i);
		i++;
	}
	fprintf(stderr, "HELOOOOO\n");
	// free(pipesfd);
	return (0);
}

int	**alloc_pipe(int i, int **pipefd)
{
	if (i == 0)
	{
		pipefd = malloc(sizeof(int *) * 2);
		if (!pipefd)
			return (fprintf(stderr, "probleme happend in alloc_pipe"), NULL);
		pipe(pipefd[0]);
	}
	if (i % 2 == 0)
	{
		pipe(pipefd[0]);
		// pipefd = malloc(sizeof(int) * 2);
	}
	else
	{
		pipe(pipefd[1]);
		// pipefd = malloc(sizeof(int) * 2);
	}
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
