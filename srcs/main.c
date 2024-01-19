/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:00:57 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/19 13:37:08 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**	This function takes as parameter: 
**
**  int argc
**	Char *argv
**	char *envp
**
** =====================================================
** =====================================================
**
** we create the fd1 and fd4 in create_fd
** with the flags :
** fd1 = O_RDONLY = read only so we can read but not modify
** fd4 = O_WRONLY = Write Only we can write but not read
** fd4 = O_CREAT = to create file if does not exist
** fd4 = O_TRUNC = To change the file if he exist
*/

// il me faut une fonction pour les actions de l'enfant et un pour les parents
// il me faut check le fork avant

int	main(int argc, char *argv[], char *envp[])
{
	char	**new_argv;
	int		new_argc;
	char	**buf;
	char	*fre;

	(void)argc;
	new_argv = NULL;
	new_argv = get_new_argv(argv);
	new_argc = found_max(new_argv);
	int i = 0;
	while (new_argv[i])
	{
		// fprintf(stderr, "%s\n", new_argv[i]);
		buf = arg(new_argv[i]);
		fre = ft_do_process(envp, buf[0], 0, 0);
		if (fre != NULL)
			fprintf(stderr, "success\n");
		else
		{
			ft_freedb_essaie(buf);
			ft_freedb_essaie(new_argv);
			return (0);
		}
		ft_freedb_essaie(buf);
		free(fre);
		i++;
	}
	fprintf(stderr, "%d\n", new_argc);
	ft_pipex(new_argv, envp, new_argc);
	waitpid(-1, NULL, 0);
	ft_freedb_essaie(new_argv);
	fprintf(stderr, "TOUT EST FINIS\n");
	return (0);
	// fprintf(stderr, "==avant pipex==\n");
	// if (argc == 2)
	// {
	// 	pipefd = NULL;
	// 	(void)pipefd;
	// 	// pipefd = alloc_pipe(0, pipefd);
	// 	// if (!pipefd[1] || !pipefd[0])
	// 	// 	return (free(pipefd), -1);
	// 	// fprintf(stderr, "je passe par la et voici mon argv %s\n", new_argv[0]);
	// 	// fprintf(stderr, "je passe par la et voici mon argv %s\n", argv[1]);
	// 	fprintf(stderr, "je passe bien par single\n");
	// 	child_process_single(pipefd, argv, envp, 0);
	// 	ft_freedb_essaie(new_argv);
	// 	return (0);
	// }
	// else
	// {
	// 	fprintf(stderr, "je passe bien par MUUUULTIIII\n");
	// 	// ft_pipex(new_argv, envp, new_argc);
	// }
	// fprintf(stderr, "FIN DU PROGRAMME\n");
}

void	ft_freedb_essaie(char *new_argv[])
{
	int	i;

	i = 0;
	while (new_argv[i])
	{
		free(new_argv[i]);
		i++;
	}
	free(new_argv);
}

char	**get_new_argv(char *argv[])
{
	int		i;
	int		j;
	int		c;
	char	**buf;
	int		len;

	i = 1;
	c = 0;
	buf = malloc(sizeof(char *) * found_max(argv));
	if (!buf)
		return (printf("malloc problem at new_argv\n"), NULL);
	while (argv[i])
	{
		j = 0;
		if (verif_arg_fd(argv, i) == -1)
		{
			len = len_fd_tab(argv, i) + 1;
			buf[c] = malloc(sizeof(char) * len);
			if (!buf[c])
				return (printf("malloc problem at new_argv\n"), free(buf), NULL);
			while (argv[i][j])
			{
				buf[c][j] = argv[i][j];
				j++;
			}
			buf[c][j] = '\0';
			c++;
		}
		i++;
	}
	buf[c] = '\0';
	return (buf);
}

int	verif_arg_fd(char *argv[], int i)
{
	int		fd;

	fd = open(argv[i], O_RDONLY, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

// // corriger les free
// char	**get_new_argv(char *argv[])
// {
// 	int		i;
// 	int		j;
// 	int		c;
// 	char	**buf;
// 	int		len;

// 	i = 1;
// 	c = 0;
// 	buf = malloc(sizeof(char *) * found_max(argv));
// 	if (!buf)
// 		return (printf("malloc problem at new_argv\n"), NULL);
// 	while (argv[i])
// 	{
// 		j = 0;
// 		len = len_fd_tab(argv, i) + 1;
// 		buf[c] = malloc(sizeof(char) * len);
// 		if (!buf[c])
// 			return (printf("malloc problem at new_argv\n"), free(buf), NULL);
// 		while (argv[i][j])
// 		{
// 			buf[c][j] = argv[i][j];
// 			j++;
// 		}
// 		buf[c][j] = '\0';
// 		c++;
// 		i++;
// 	}
// 	buf[c] = '\0';
// 	return (buf);
// }

int		len_fd_tab(char **str, int i)
{
	int		j;

	j = 0;
	while (str[i][j])
		j++;
	return (j);
}

int	found_max(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
