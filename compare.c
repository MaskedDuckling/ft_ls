#include "main.h"

int name_compare(struct dirent *a, struct dirent *b)
{
	int ia = 0; 
	int ib = 0;
	char *ca = a->d_name;
	char *cb = b->d_name;
	
	while (ca[ia] && cb[ib])
	{
		while (ca[ia] == '.')
			ia++;
		while (cb[ib] == '.')
			ib++;
		if (lower(ca[ia]) != lower(cb[ib]))
			return lower(ca[ia]) - lower(cb[ib]);
		ia++;
		ib++;
	}
	return ca[ia] - cb[ib];
}

int time_compare(struct dirent *a, struct dirent *b)
{
	struct stat st_a;
	struct stat st_b;

	stat(a->d_name, &st_a);
	stat(b->d_name, &st_b);
	return st_a.st_mtime - st_b.st_mtime;
}

void sort_tab(struct dirent **tab, int size, int reversed, int(*comp)(struct dirent *a, struct dirent *b))
{
	int i = 0;
	struct dirent *tmp;

	while (i < size - 1)	{
		if (comp(tab[i], tab[i + 1]) == 0)
			i++;
		else if ((comp(tab[i], tab[i + 1]) > 0) ^ reversed)	{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

int name_compare_char(char *a, char *b)
{
	int ia = 0; 
	int ib = 0;
	
	while (a[ia] && b[ib])
	{
		while (a[ia] == '.')
			ia++;
		while (b[ib] == '.')
			ib++;
		if (lower(a[ia]) != lower(b[ib]))
			return lower(a[ia]) - lower(b[ib]);
		ia++;
		ib++;
	}
	return a[ia] - b[ib];
}

int time_compare_char(char *a, char *b)
{
	struct stat st_a;
	struct stat st_b;

	stat(a, &st_a);
	stat(b, &st_b);
	return st_a.st_mtime - st_b.st_mtime;
}

void sort_tab_char(char **tab, int size, int reversed, int(*comp)(char *a, char *b))
{
	int i = 0;
	char *tmp;

	while (i < size - 1)	{
		if (comp(tab[i], tab[i + 1]) == 0)
			i++;
		else if ((comp(tab[i], tab[i + 1]) > 0) ^ reversed)	{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}