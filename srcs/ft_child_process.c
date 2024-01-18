/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:58:51 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/18 15:20:37 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_process_in(int **pipesfd, char **argv, char **env, int i)
{
	char		**cmd_argument;
	char		*cmd;
	char		**buf;

	fprintf(stderr, "in %s %d\n", argv[i], i);
	// fprintf(stderr, "VERIFICATOPN DANS INN!!!!!\n");
	// int j = 0;
	// while (env[j])
	// {
	// 	fprintf(stderr, "%s\n", env[j]);
	// 	j++;
	// }
	// j = 0;
	// fprintf(stderr, "MAINTENANT ARGV\n");
	// while (argv[j])
	// {
	// 	fprintf(stderr, "%s\n", argv[j]);
	// 	j++;
	// }
	// fprintf(stderr, "FIN DES VERIFICATOPN DANS INN!!!!!\n");
	if (dup2(STDIN_FILENO, STDIN_FILENO) < 0)
		return (printf("problem with dup2"), -1);
	if (dup2(pipesfd[1][1], STDOUT_FILENO) < 0)
		return (printf("problem with dup2"), -1);
	close(pipesfd[1][1]);
	buf = arg(argv[i]);
	fprintf(stderr, "buf de 0 = %s\n", buf[0]);
	cmd = ft_do_process(env, buf[0], pipesfd, i);
	cmd_argument = ft_split(argv[i], ' ');
	execve(cmd, cmd_argument, env);
	perror("execve");
	free(cmd);
	free(cmd_argument);
	free(pipesfd[0]);
	free(pipesfd[1]);
	exit(0);
	return (0);
}

int	child_process_middle(int **pipesfd, char **argv, char **env, int i)
{
	char		**cmd_argument;
	char		*cmd;

	fprintf(stderr, "mid %s %d\n", argv[i], i);
	if (i % 2 == 1)
	{
		// close(pipesfd[1][0]);
		// close(pipesfd[0][1]);
		if (dup2(pipesfd[0][0], STDIN_FILENO) < 0)
			return (printf("problem with dup2"), -1);
		close(pipesfd[0][0]);
		// close(pipesfd[1].pipes[0])
		if (dup2(pipesfd[1][1], STDOUT_FILENO) < 0)
			return (printf("problem with dup2"), -1);
		close(pipesfd[1][1]);
	}
	else
	{
		// close(pipesfd[1][1]);
		// close(pipesfd[0][0]);
		if (dup2(pipesfd[1][0], STDIN_FILENO) < 0)
			return (printf("problem with dup2"), -1);
		close(pipesfd[1][0]);
		// close(pipesfd[0].pipes[0])
		if (dup2(pipesfd[0][1], STDOUT_FILENO) < 0)
			return (printf("problem with dup2"), -1);
		close(pipesfd[0][1]);
	}
	cmd = ft_do_process(env, argv[i], pipesfd, i);
	cmd_argument = ft_split(argv[i], ' ');
	execve(cmd, cmd_argument, env);
	free(cmd);
	free(cmd_argument);
	free(pipesfd[0]);
	free(pipesfd[1]);
	exit(0);
	return (0);
}

int	child_process_out(int **pipesfd, char **argv, char **env, int i)
{
	char		**cmd_argument;
	char		*cmd;
	char		**buf;

	fprintf(stderr, "je suis dans out %s %d\n", argv[i], i);
	if (i % 2 == 1)
	{
		// close(pipesfd[0][0]);
		// close(pipesfd[0][1]);
		// close(pipesfd[1][0]);
		// close(pipesfd[1][1]);
		fprintf(stderr, "JE SUIS DANS I %% 2 == 1\n");
		if (dup2(pipesfd[1][0], 0) < 0)
			return (free(pipesfd), printf("problem with dup2"), -1);
		close(pipesfd[1][0]);
		// close(pipesfd[0][1]);
		// close(pipesfd[0][0]);
		if (dup2(STDOUT_FILENO, 1) < 0)
			return (free(pipesfd), printf("problem with dup2"), -1);
	}
	else
	{
		fprintf(stderr, "JE SUIS DANS I %% 2 == 0\n");
		close(pipesfd[0][1]);
		if (dup2(pipesfd[0][0], 0) < 0)
			return (free(pipesfd), printf("problem with dup2"), -1);
		close(pipesfd[0][0]);
		if (dup2(STDOUT_FILENO, 1) < 0)
			return (free(pipesfd[0]), free(pipesfd[1]), free(pipesfd), printf("problem with dup2"), -1);
	}
	buf = arg(argv[i]);
	fprintf(stderr, "buf de 0 = %s\n", buf[0]);
	cmd = ft_do_process(env, buf[0], pipesfd, i);
	cmd_argument = ft_split(argv[i], ' ');
	fprintf(stderr, "cmd a la sortie: %s\n", cmd);
	if (!cmd)
	{
		fprintf(stderr, "donc probleme avec cmd\n");
		free(cmd);
		free(cmd_argument);
		return (-1);
	}
	else if (!cmd_argument)
	{
		fprintf(stderr, "donc probleme avec cmd_arg\n");
		free(cmd);
		free(cmd_argument);
		return (-1);
	}
	fprintf(stderr, "cmd a la sortie: %s\n", cmd);
	execve(cmd, cmd_argument, env);
	perror("execve");
	free(cmd);
	free(cmd_argument);
	free(pipesfd[0]);
	free(pipesfd[1]);
	exit(0);
	return (0);
}

char	**arg(char str[])
{
	char	**buf;

	buf = ft_split(str, ' ');
	return (buf);
}

int	child_process_single(int **pipesfd, char **argv, char **env, int i)
{
	(void)pipesfd;
	char		**cmd_argument;
	char		*cmd;

	// cmd_argument = NULL;
	// (void)i;
	// (void)argv;
	// (void)env;
	// fprintf(stderr, "je suis dans out %s %d\n", argv[i], i);
	// if (dup2(STDIN_FILENO, STDIN_FILENO) < 0)
	// 	return (printf("problem with dup2"), -1);
	// if (dup2(STDOUT_FILENO, 1) < 0)
	// 	return (printf("problem with dup2"), -1);
	// close(pipesfd[0][1]);
	// close(pipesfd[0][0]);
	// close(pipesfd[1][0]);
	// close(pipesfd[1][1]);
	// fprintf(stderr, "Avant execve : cmd_tout_cours = %s\n", cmd);
	cmd = ft_do_process(env, argv[1], pipesfd, i);
	cmd_argument = ft_split(argv[1], ' ');
	execve(cmd, cmd_argument, env);
	return (0);
}

/*
int	child_process_in(int **pipesfd, char **argv, char **env, int i)
{
	fprintf(stderr, "in %s %d\n", argv[i], i);
	if (dup2(STDIN_FILENO, STDIN_FILENO) < 0)
		return (printf("problem with dup2"), -1);
	// close(pipesfd[i].pipes[0])
	close(pipesfd[0][1]);
	if (dup2(pipesfd[1][1], STDOUT_FILENO) < 0)
		return (printf("problem with dup2"), -1);
	close(pipesfd[1][1]);
	if (ft_do_process(env, argv[i]) == -1)
		return (free(pipesfd[0]), free(pipesfd[1]), free(pipesfd), -1);
	return (0);
}

int	child_process_middle(int **pipesfd, char **argv, char **env, int i)
{
	fprintf(stderr, "mid %s %d\n", argv[i], i);
	if (i % 2 == 1)
	{
		close(pipesfd[0][1]);
		if (dup2(pipesfd[0][0], STDIN_FILENO) < 0)
			return (printf("problem with dup2"), -1);
		close(pipesfd[0][0]);
		// close(pipesfd[1].pipes[0])
		if (dup2(pipesfd[1][1], STDOUT_FILENO) < 0)
			return (printf("problem with dup2"), -1);
		close(pipesfd[1][1]);
		close(pipesfd[1][0]);
	}
	else
	{
		close(pipesfd[1][1]);
		if (dup2(pipesfd[1][0], STDIN_FILENO) < 0)
			return (printf("problem with dup2"), -1);
		close(pipesfd[1][0]);
		// close(pipesfd[0].pipes[0])
		if (dup2(pipesfd[0][1], STDOUT_FILENO) < 0)
			return (printf("problem with dup2"), -1);
		close(pipesfd[0][1]);
		close(pipesfd[0][0]);
	}
	ft_do_process(env, argv[i]);
	return (0);
}

int	child_process_out(int **pipesfd, char **argv, char **env, int i)
{
	fprintf(stderr, "je suis dans out %s %d\n", argv[i], i);
	if (i % 2 == 1)
	{
		close(pipesfd[1][1]);
		close(pipesfd[0][0]);
		close(pipesfd[0][1]);
		if (dup2(pipesfd[1][0], 0) < 0)
			return (free(pipesfd), printf("problem with dup2"), -1);
		close(pipesfd[1][0]);
		if (dup2(STDOUT_FILENO, 1) < 0)
			return (free(pipesfd), printf("problem with dup2"), -1);
	}
	else
	{
		close(pipesfd[1][1]);
		close(pipesfd[1][0]);
		close(pipesfd[0][1]);
		if (dup2(pipesfd[0][0], 0) < 0)
			return (free(pipesfd), printf("problem with dup2"), -1);
		close(pipesfd[0][0]);
		if (dup2(STDOUT_FILENO, 1) < 0)
			return (free(pipesfd[0]), free(pipesfd[1]), free(pipesfd), printf("problem with dup2"), -1);
	}
	ft_do_process(env, argv[i]);
	return (0);
}

int	child_process_single(int **pipesfd, char **argv, char **env, int i)
{
	// fprintf(stderr, "je suis dans out %s %d\n", argv[i], i);
	if (dup2(STDIN_FILENO, STDIN_FILENO) < 0)
		return (printf("problem with dup2"), -1);
	if (dup2(STDOUT_FILENO, 1) < 0)
		return (free(pipesfd[0]), free(pipesfd[1]), free(pipesfd), printf("problem with dup2"), -1);
	ft_do_process(env, argv[i]);
	return (0);
}

*/