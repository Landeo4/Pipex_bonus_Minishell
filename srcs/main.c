/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:00:57 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/15 13:24:13 by tpotilli         ###   ########.fr       */
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
** fd4 = O_TRUNC = To cahnge the file if he exist
*/

// il me faut une fonction pour les actions de l'enfant et un pour les parents
// il me faut check le fork avant

int	main(int argc, char *argv[], char *envp[])
{
	char **new_argv;
	int		new_argc;
	(void)argc;
	// (void)file;
	// (void)envp;
	// int	file[2];

	new_argv = NULL;
	// file[0] = ft_create_fd(argv[1], O_RDONLY);
	// file[1] = ft_create_fd(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
	// if (file[0] == -1 || file[1] == -1)
		// return (1);
	int i = 0;
	// fprintf(stderr, "petit calcul 0 modulo = %d\n", (0 % 2));
	new_argv = get_new_argv(argv);
	new_argc = found_max(new_argv);
	while (new_argv[i])
	{
		fprintf(stderr, "%s\n", new_argv[i]);
		i++;
	}
	ft_pipex(new_argv, envp, new_argc);
	ft_freedb_essaie(new_argv);
	fprintf(stderr, "FIN DU PROGRAMME\n");
	return (0);
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
	// close(fd);
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
