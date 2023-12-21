 #include "main.h"

char lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 'a' - 'A';
	return c;
}

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

void	print_mode(mode_t mode, unsigned char type)
{
	printf("%c%c%c%c%c%c%c%c%c%c\t",
			#include <dirent.h> // Include the necessary header file

			// ...

			type == DT_LNK ? 'l' : type == DT_DIR ? 'd' : '-',
			(mode & S_IRUSR) ? 'r' : '-',
			(mode & S_IWUSR) ? 'w' : '-',
			(mode & S_IXUSR) ? 'x' : '-',
			(mode & S_IRGRP) ? 'r' : '-',
			(mode & S_IWGRP) ? 'w' : '-',
			(mode & S_IXGRP) ? 'x' : '-',
			(mode & S_IROTH) ? 'r' : '-',
			(mode & S_IWOTH) ? 'w' : '-',
			(mode & S_IXOTH) ? 'x' : '-');
}

void set_flags_t(char *str, flags_t *flags)
{
	int i = 1;
	while (str[i]){
		if (str[i] == 'a')
			flags->a = 1;
		else if (str[i] == 'l')
			flags->l = 1;
		else if (str[i] == 'R')
			flags->R = 1;
		else if (str[i] == 'r')
			flags->r = 1;
		else if (str[i] == 't')
			flags->t = 1;
		else	{
			printf("ls: option invalide -- %c\n", str[i]);
			printf("Saisissez « ls --help » pour plus d'informations.");
			exit(1);
		}
		i++;
	}
}
