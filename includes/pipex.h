/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:39:00 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/17 15:39:00 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// =======================================================================
//								Colors
// =======================================================================

# define BLACK "\001\033[1;30m\002"
# define RED "\001\033[1;31m\002"
# define GREEN "\001\033[1;32m\002"
# define YELLOW "\001\033[1;33m\002"
# define BLUE "\001\033[1;34m\002"
# define PURPLE "\001\033[1;35m\002"
# define CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[1;37m\002"
# define RESET "\001\033[0m\002"

// =======================================================================
//								Include
// =======================================================================

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>


// =======================================================================
//								Structure
// =======================================================================

typedef struct s_pipes
{
    char	**argv;
    char	**env;
    int		pipes[2];
    char	*fd1;
    char	*fd2;
}   t_pipes;

// =======================================================================
//								Libft
// =======================================================================

int		ft_letter(char const *s, char c, int i);
char	**ft_free(char **split, int index_word);
int		ft_word(char const *s, char c);
char	**ft_copy(char const *s, char c, char **split, int i);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_check(char const *s, size_t len, unsigned int start);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
char	*ft_cpy(char const *s1, char const *s2, char *str);
char	*ft_strjoin(char *s1, char *s2);

// =======================================================================
//								Pipex
// =======================================================================

int     ft_parsing(int argc);
int		ft_verif_error(char *buff, int fd[]);
int		ft_create_fd(char *argv, int flag);
char	*ft_get_pass(char *argv, char *envp, int i);
char	*ft_do_process(char *envp[], char *cmd, int **pipefd, int i);
char	**ft_take_line(char **big, char *little);
void	ft_freedb(char **str);
void	ft_execute(char	*cmd, char	**env);
char	*ft_strjoin_free(char *s1, char *s2);
char	**ft_get_path(char **env);
char	*ft_strchr(const char *string, int searchedChar);
char	*str_join_free(char *path, char *cmd);


t_pipes	*init_struct();
int		found_max(char **argv);
int		get_nb_pipes(char **argv);
char	**get_new_argv(char *argv[]);
int		verif_arg_fd(char *argv[], int i);
int		len_fd_tab(char **str, int i);

void    ft_freedb_essaie(char *new_argv[]);
int		ft_pipex(char *argv[], char *env[], int argc);
int		process(char *cmd, char *env[], int token);

int		child_process_middle(int **pipesfd, char **argv, char **env, int i);
int		child_process_unpair(int **pipesfd, char **argv, char **env, int i);
int		child_process_in(int **pipesfd, char **argv, char **env,int i);
int		child_process_out(int **pipesfd, char **argv, char **env, int i);
int		parent_process(int **pipefd);
int		**alloc_pipe(int i, int **pipefd);
int		child_process_single(int **pipesfd, char **argv, char **env, int i);


#endif
