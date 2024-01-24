#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

typedef struct	flags_t_s
{
	int a;
	int l;
	int R;
	int r;
	int t;
}				flags_t;


/*LIBFT*/
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);

void    sort_tab(struct dirent **tab, int size, int reversed, int(*comp)(struct dirent *a, struct dirent *b));
int     time_compare(struct dirent *a, struct dirent *b);
int     name_compare(struct dirent *a, struct dirent *b);
void 	sort_tab_char(char **tab, int size, int reversed, int(*comp)(char *a, char *b));
int     time_compare_char(char *a, char *b);
int     name_compare_char(char *a, char *b);

void	set_flags_t(char *str, flags_t *flags);
void    print_mode(mode_t mode, unsigned char type);
void    print_time(struct stat st);
void	ft_ls(char *dir, flags_t flags);
char 	lower(char c);


//GERER LS SUR UN FICHIER

# endif