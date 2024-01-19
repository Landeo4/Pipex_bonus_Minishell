/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:19:12 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/19 20:56:52 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*int		ft_do_process(char *envp[], char *cmd, int **pipesfd, int j)
{
	int		i;
	char	**path;
	char	**cmd_argument;
	char	*buf;
	char	*buf2;
	(void)pipesfd;
	(void)j;

	// fprintf(stderr, "command = %s et identifiant %d\n", cmd, id);
	i = 0;
	cmd_argument = ft_split(cmd, ' ');
	path = ft_get_path(envp);
	// fprintf(stderr, "je suis dans process voici mon identifiant %d et mon i avant la boucle %d\n", id, i);
	while (path[i])
	{
		buf = ft_strjoin(path[i], "/");
		// path[i] = str_join_free(path[i], cmd_argument[0]);
		if (cmd[0] == '/')
			buf2 = ft_strjoin(path[i], cmd);
		else
			buf2 = ft_strjoin(buf, cmd);
		// fprintf(stderr, "je suis avant execve ma commande %s, et path %s\n", cmd, path[i]);
		fprintf(stderr, "--------------------\n");
		fprintf(stderr, "Avant execve : path[i] = %s\n", path[i]);
		fprintf(stderr, "Avant execve : cmd_tout_cours = %s\n", cmd);
		fprintf(stderr, "Avant execve : cmd_argument = %s\n", cmd_argument[0]);
		fprintf(stderr, "Avant execve : i = %d\n", i);
		if (access(buf2, 0) == 0)
		{
			int j = 0;
			fprintf(stderr, "access est ok======\n donc voici mes args\npath[i] %s\n", path[i]);
			while (cmd_argument[j])
			{
				fprintf(stderr, "cmd_arg = %s\n", cmd_argument[j]);
				j++;
			}
			fprintf(stderr, "===============\n");
			if (execve(path[i], cmd_argument, envp) == -1)
			{
				perror("execve a echouer c'est dommage");
				fprintf(stderr, "Path: %s\n", path[i]);
			}
		}
		free(buf);
		free(buf2);
		free(path[i]);
		fprintf(stderr, "--------------------\n");
		// fprintf(stderr, "je suis apres execve \n");
		i++;
	}
	// fprintf(stderr, "je sors de ma boucle\n");
	free(path);
	// execve(cmd_argument[0], cmd_argument, envp);
	ft_freedb(cmd_argument);
	fprintf(stderr, "execve a echoue je suis a la fin de la fonction: %s\n", strerror(errno));
	return (-1);
}

// fprintf(stderr, "Avant execve : path[i] = %s\n", path[i]);
// fprintf(stderr, "Avant execve : buf2 = %s\n", buf2);
// fprintf(stderr, "Avant execve : i = %d\n", i);
*/

char	*ft_do_process(char *envp[], char *cmd, int **pipesfd, int j)
{
	int		i;
	char	**path;
	char	*buf;
	char	*buf2;
	(void)pipesfd;
	(void)j;

	i = 0;
	path = ft_get_path(envp);
	// fprintf(stderr, "VERIFICATOPN DANS EXECUTE!!!!\n");
	// while (envp[c])
	// {
	// 	fprintf(stderr, "%s\n", envp[c]);
	// 	c++;
	// }
	// c = 0;
	// fprintf(stderr, "MAINTENANT ARGV\n");
	fprintf(stderr, "commande dans do process %s\n", cmd);
	// fprintf(stderr, "FIN DES VERIFICATOPN DANS EXECUTE!!!!!\n");
	while (path[i])
	{
		buf = ft_strjoin(path[i], "/");
		buf2 = ft_strjoin(buf, cmd);
		free(buf);
		if (access(buf2, 0) == 0)
		{
			fprintf(stderr, "donc buf2 = %s\n", buf2);
			free(path[i]);
			while (path[i++])
				free(path[i]);
			free(path);
			return (buf2);
		}
		free(buf2);
		free(path[i]);
		i++;
	}
	free(path);
	fprintf(stderr, "======TOUT A ECHOUER DANS FT_DO_PROCESS====== %s\n", cmd);
	return (NULL);
}

char	**ft_get_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		perror("Error: PATH not found");
	path = ft_split(env[i] + 5, ':');
	return (path);
}

char *str_join_free(char *path, char *cmd)
{
	char *str;
	
	str = ft_strjoin(path, cmd);
	free(path);
	return (str);
}

void	ft_freedb(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
