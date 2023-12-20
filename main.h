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

void    sort_tab(struct dirent **tab, int size, int reversed, int(*comp)(struct dirent *a, struct dirent *b));
int     time_sort(struct dirent *a, struct dirent *b);
int     alpha_sort(struct dirent *a, struct dirent *b);
void    print_mode(mode_t mode);
void    print_time(struct stat st);


# endif