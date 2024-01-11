/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotillion <tpotillion@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:19:12 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/06 07:53:08 by tpotillion       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_do_process(char *envp[], char *cmd)
{
	int		i;
	char	**path;
	char	**cmd_argument;

	// fprintf(stderr, "command = %s et identifiant %d\n", cmd, id);
	i = 0;
	cmd_argument = ft_split(cmd, ' ');
	path = ft_get_path(envp);
	// fprintf(stderr, "je suis dans process voici mon identifiant %d et mon i avant la boucle %d\n", id, i);
	while (path[i])
	{
		path[i] = str_join_free(path[i], "/");
		path[i] = str_join_free(path[i], cmd_argument[0]);
		// fprintf(stderr, "je suis avant execve ma commande %s, et path %s\n", cmd, path[i]);
		// fprintf(stderr, "je suis avant execve (%d)\n", id);
		execve(path[i], cmd_argument, envp);
		// fprintf(stderr, "je suis apres execve (%d)\n", id);
		i++;
	}
	// fprintf(stderr, "je sors de ma boucle\n");
	ft_freedb(path);
	execve(cmd_argument[0], cmd_argument, envp);
	ft_freedb(cmd_argument);
	return ;
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
