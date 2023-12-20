 #include "main.h"

int alpha_sort(struct dirent *a, struct dirent *b)
{
	int ia = 0; 
	int ib = 0;
	
	while (a->d_name[ia] == '.')
		ia++;
	while (b->d_name[ib] == '.')
		ib++;
	return strcmp(a->d_name + ia, b->d_name + ib);
}

int time_sort(struct dirent *a, struct dirent *b)
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
	
	(void)	reversed;
	while (i < size - 1)	{
		if (comp(tab[i], tab[i + 1]) > 0)	{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

void print_time(struct stat st)
{
	time_t t = st.st_mtime;
	struct tm *time = gmtime(&t);
	time->tm_hour += 1;
	char *str = asctime(time);
	int i = 4;
	while (i < 16){
		printf("%c", str[i]);
		i++;
	}
	printf("\t");
}

void	print_mode(mode_t mode)
{
	printf("%c", S_ISDIR(mode) ? 'd' : '-');
	printf("%c", (mode & S_IRUSR) ? 'r' : '-');
	printf("%c", (mode & S_IWUSR) ? 'w' : '-');
	printf("%c", (mode & S_IXUSR) ? 'x' : '-');
	printf("%c", (mode & S_IRGRP) ? 'r' : '-');
	printf("%c", (mode & S_IWGRP) ? 'w' : '-');
	printf("%c", (mode & S_IXGRP) ? 'x' : '-');
	printf("%c", (mode & S_IROTH) ? 'r' : '-');
	printf("%c", (mode & S_IWOTH) ? 'w' : '-');
	printf("%c\t", (mode & S_IXOTH) ? 'x' : '-');
}
