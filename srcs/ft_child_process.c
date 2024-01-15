/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:58:51 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/15 14:43:24 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_process_in(int **pipesfd, char **argv, char **env, int i)
{
	fprintf(stderr, "in\n");
	if (dup2(STDIN_FILENO, STDIN_FILENO) < 0)
		return (printf("problem with dup2"), -1);
	// close(pipesfd[i].pipes[0])
	if (i % 2 == 1)
	{
		if (dup2(pipesfd[1][1], STDOUT_FILENO) < 0)
			return (printf("problem with dup2"), -1);
		close(pipesfd[1][1]);
	}
	else //0 pair et 1 impair
	{
		if (dup2(pipesfd[0][1], STDOUT_FILENO) < 0)
			return (printf("problem with dup2"), -1);
		close(pipesfd[0][1]);
	}
	ft_do_process(env, argv[i]);
	exit(0);
}//donc la c'est pour la premiere fois

int	child_process_middle(int **pipesfd, char **argv, char **env, int i)
{
	fprintf(stderr, "mid\n");
	if (i % 2 == 1)
	{
		if (dup2(pipesfd[0][0], STDIN_FILENO) < 0)
			return (printf("problem with dup2"), -1);
		close(pipesfd[0][0]);
		// close(pipesfd[1].pipes[0])
		if (dup2(pipesfd[1][1], STDOUT_FILENO) < 0)
			return (printf("problem with dup2"), -1);
	}
	else
	{
		if (dup2(pipesfd[1][0], STDIN_FILENO) < 0)
			return (printf("problem with dup2"), -1);
		close(pipesfd[1][0]);
		// close(pipesfd[0].pipes[0])
		if (dup2(pipesfd[0][1], STDOUT_FILENO) < 0)
			return (printf("problem with dup2"), -1);
	}
	close(pipesfd[1][1]);
	ft_do_process(env, argv[i]);
	exit(0);
}

int	child_process_out(int **pipesfd, char **argv, char **env, int i)
{
	fprintf(stderr, "je suis dans out %s %d\n", argv[i], i);
	if (i % 2 == 1)
	{
		if (dup2(pipesfd[1][0], 0) < 0)
			return (free(pipesfd), printf("problem with dup2"), -1);
		close(pipesfd[0][0]);
		if (dup2(STDOUT_FILENO, 0) < 0)
			return (free(pipesfd), printf("problem with dup2"), -1);
	}
	else
	{
		if (dup2(pipesfd[0][0], 0) < 0)
			return (free(pipesfd), printf("problem with dup2"), -1);
		close(pipesfd[0][0]);
		if (dup2(STDOUT_FILENO, 0) < 0)
			return (free(pipesfd), printf("problem with dup2"), -1);
	}
	ft_do_process(env, argv[i]);
	exit(0);
}

// int	parent_process(t_pipes *pipesfd, char **argv, char **env, int i)
// {
// 	(void)argv;
// 	if (dup2(pipesfd[i - 1].pipes[0], 0) < 0)
// 		return (free(pipesfd), printf("problem with dup2"), -1);
// 	// close(pipesfd[i - 1].pipes[0]);
// 	// close(pipesfd[i].pipes[1]);
// 	if (dup2(pipesfd[i].pipes[0], 0) < 0)
// 		return (free(pipesfd), printf("problem with dup2"), -1);
// 	return (0);
// }

// int	child_process_unpair(t_pipes *pipesfd, char **argv, char **env,)
// {
// 	if (i % 2 == 1)
// 	{
// 		if (dup2(pipefd[0].pipes[0], STDIN_FILENO) < 0)
// 			return (free(pipesfd), printf("problem with dup2"), -1);
// 		// close(pipesfd[1].pipes[0])
// 		if (dup2(pipefd[1].pipes[1], STDOUT_FILENO) < 0)
// 			return (free(pipesfd), printf("problem with dup2"), -1);
// 		ft_do_process(env, argv[i]);
// 	}
// 	else
// 	{
// 		if (dup2(pipefd[1].pipes[0], STDIN_FILENO) < 0)
// 			return (free(pipesfd), printf("problem with dup2"), -1);
// 		// close(pipesfd[0].pipes[0])
// 		if (dup2(pipefd[0].pipes[1], STDOUT_FILENO) < 0)
// 			return (free(pipesfd), printf("problem with dup2"), -1);
// 		ft_do_process(env, argv[i]);
// 	}
// }

// int	child_process_out(t_pipes *pipesfd, char **argv, char **env)
// {
// 	if (dup2(pipefd[i - 1].pipes[0]) < 0)
// 		return (free(pipesfd), printf("problem with dup2"), -1);
// 	close(pipesfd[i - 1].pipes[0])
// 	if (dup2(pipefd[i], 0) < 0)
// 		return (free(pipesfd), printf("problem with dup2"), -1);
// }

/*save importante

int	child_process_in(t_pipes *pipes, int i, char *env[], char *argv[])
{
	int	fd;

	close(pipes->pipes[0]);
	// fprintf(stderr, "pipes[i].fd1 = %s\n", pipes[0].fd1);
	fd = ft_create_fd(pipes[0].fd1, O_RDONLY); // trouver nom fichier argv[4]
	if (fd < 0)
		return (close(pipes->pipes[1]), -1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (close(pipes->pipes[1]), close(fd), perror("dup2"), -1);
	close(fd);
	if (dup2(pipes[i].pipes[1], STDOUT_FILENO) < 0)
		return (close(pipes->pipes[1]), perror("dup2"), -1);
	close(pipes->pipes[1]);
	ft_do_process(env, argv[0], i);
	return (0);
}
// [penser a regler probleme de dup2] car le retour en cas d'erreur fonctionne mal
int	child_process_middle(t_pipes *pipes, int i, char *env[], char *argv[])
{
	close(pipes->pipes[0]);
	// close(pipes[i - 1].pipes[1]);
	fprintf(stderr, "je suis au tout debut de middle\ni = %d\n", i);
	fprintf(stderr, "permier duo2\n");
	if (dup2(pipes[i - 1].pipes[0], STDIN_FILENO) < 0)
		return (close(pipes[i - 1].pipes[0]), perror("dup2"), -1);
	close(pipes[i - 1].pipes[0]);
	fprintf(stderr, "second duo2\n");
	if (dup2(pipes[i].pipes[1], STDOUT_FILENO) < 0)
		return (close(pipes[i].pipes[1]), perror("dup2"), -1);
	fprintf(stderr, "salut\n");
	fprintf(stderr, "resultat dans middle %d\n", pipes[i].pipes[1]);
	close(pipes->pipes[1]);
	ft_do_process(env, argv[i], i);
	return (0);
}

int	child_process_out(t_pipes *pipes, int i, char *env[], char *argv[])
{
	int		fd;

	close(pipes[i].pipes[0]);
	close(pipes[i].pipes[1]);
	if (dup2(pipes[i - 1].pipes[0], STDIN_FILENO) < 0)
		return (close(pipes[i - 1].pipes[0]), perror("dup2"), -1);
	fprintf(stderr, "voici result dans out %d\n", pipes[i - 1].pipes[0]);
	fprintf(stderr, "pipes[i].fd2 = %s\n", pipes[0].fd2);
	fd = ft_create_fd(pipes[0].fd2, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (close(pipes->pipes[0]), close(fd), perror("dup2"), -1);
	close(fd);
	fprintf(stderr, "i = %d\n", i);
	fprintf(stderr, "argv[i] = %s\n", argv[i]);
	close(pipes[i - 1].pipes[0]);
	close(pipes->pipes[1]);
	ft_do_process(env, argv[i], i);
	return (0);
}
*/

/*
**	This function takes as parameter: 
**
**	int fd
**	char *argv[], 
**  char *envp[],
**  int *end
**
** =====================================================
** =====================================================
**
** 
*/

// int	child_process_in(t_pipes *pipes, int i, char *env[], char *argv[])
// {
// 	int	fd;

// 	close(pipes[i].pipes[0]);
// 	// fprintf(stderr, "pipes[i].fd1 = %s\n", pipes[0].fd1);
// 	fd = ft_create_fd(pipes[0].fd1, O_RDONLY); // trouver nom fichier argv[4]
// 	if (fd < 0)
// 		return (close(pipes->pipes[1]), -1);
// 	if (dup2(fd, STDIN_FILENO) < 0)
// 		return (close(pipes->pipes[1]), close(fd), perror("dup2"), -1);
// 	close(fd);
// 	if (dup2(pipes[i].pipes[1], STDOUT_FILENO) < 0)
// 		return (close(pipes->pipes[1]), perror("dup2"), -1);
// 	close(pipes[i].pipes[1]);
// 	ft_do_process(env, argv[0], i);
// 	return (0);
// }
// // [penser a regler probleme de dup2] car le retour en cas d'erreur fonctionne mal
// int	child_process_middle(t_pipes *pipes, int i, char *env[], char *argv[])
// {
// 	int	fd;
// 	// close(pipes[i - 1].pipes[1]);
// 	fprintf(stderr, "je suis au tout debut de middle\ni = %d\n", i);
// 	if (dup2(pipes[i - 1].pipes[0], STDIN_FILENO) < 0)
// 		return (close(pipes[i - 1].pipes[0]), perror("dup2"), -1);
// 	close(pipes[i - 1].pipes[0]);
// 	close(pipes[i - 1].pipes[1]);
// 	fd = ft_create_fd("test2v", O_WRONLY | O_CREAT | O_TRUNC);
// 	if (fd < 0)
// 		return (-1);
// 	if (dup2(fd, STDOUT_FILENO) < 0)
// 		return (close(pipes->pipes[0]), close(fd), perror("dup2"), -1);
// 	close(fd);
// 	ft_do_process(env, argv[i], i);
// 	return (0);
// }

// int	child_process_out(t_pipes *pipes, int i, char *env[], char *argv[])
// {
// 	int		fd;

// 	// close(pipes[i].pipes[0]);
// 	// close(pipes[i].pipes[1]);
// 	if (dup2(pipes[i - 1].pipes[0], STDIN_FILENO) < 0)
// 		return (close(pipes[i - 1].pipes[0]), perror("dup2"), -1);
// 	close(pipes[i - 1].pipes[0]);
// 	close(pipes[i - 1].pipes[1]);
// 	fprintf(stderr, "OUT voici result dans out %d\n", pipes[i - 1].pipes[0]);
// 	fprintf(stderr, "OUT pipes[i].fd2 = %s\n", pipes[0].fd2);
// 	fd = ft_create_fd(pipes[0].fd2, O_WRONLY | O_CREAT | O_TRUNC);
// 	if (fd < 0)
// 		return (-1);
// 	if (dup2(fd, STDOUT_FILENO) < 0)
// 		return (close(pipes->pipes[0]), close(fd), perror("dup2"), -1);
// 	close(fd);
// 	fprintf(stderr, "OUT i = %d\n", i);
// 	fprintf(stderr, "OUT argv[i] = %s\n", argv[i]);
// 	close(pipes->pipes[1]);
// 	close(pipes->pipes[0]);
// 	ft_do_process(env, argv[i], i);
// 	return (0);
// }

// void	child_process_start(char *argv[], char *envp[], int *end)
// {
// 	int	fd;

// 	close(end[0]);
// 	fd = ft_create_fd(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (close(end[1]), exit(errno));
// 	if (dup2(fd, STDIN_FILENO) < 0)
// 		return (close(end[1]), close(fd), perror("dup2"), exit(errno));
// 	close(fd);
// 	if (dup2(end[1], STDOUT_FILENO) < 0)
// 		return (close(end[1]), perror("dup2"), exit(errno));
// 	close(end[1]);
// 	ft_do_process(envp, argv[2]);
// }

// void	child_process_end(char *argv[], char *envp[], int *end)
// {
// 	int		fd;

// 	close (end[1]);
// 	if (dup2(end[0], STDIN_FILENO) < 0)
// 		return (close(end[0]), perror("dup2"), exit(errno));
// 	close(end[0]);
// 	fd = ft_create_fd(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
// 	if (fd < 0)
// 		return (exit(errno));
// 	if (dup2(fd, STDOUT_FILENO) < 0)
// 		return (close(end[0]), close(fd), perror("dup2"), exit(errno));
// 	close (fd);
// 	ft_do_process(envp, argv[3]);
// }

// void	ft_close(int *fd)
// {
// 	if (*fd >= 3)
// 	{
// 		close(*fd);
// 		*fd = -2;
// 	}
// }

// void	ft_free(void **ptr)
// {
// 	if (*ptr)
// 	{
// 		free(*ptr);
// 		*ptr = NULL;
// 	}
// }