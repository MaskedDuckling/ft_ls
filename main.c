#include "main.h"

struct dirent **get_items(DIR *dh, int *size, flags_t flags)
{
	struct dirent **tab = malloc(sizeof(struct dirent*) * 100);
	struct dirent *d;
	int i = 0;

	while ((d = readdir(dh)) != NULL)	{
		tab[i] = d;
		i++;
	}
	*size = i;

	if (flags.t)
		sort_tab(tab, *size, flags.r, time_sort);
	else
		sort_tab(tab, *size, flags.r, alpha_sort);

	return tab;
}

void display(struct dirent **tab, int size, flags_t flags)
{
	struct stat		st;
	struct dirent	*d;
	int 			i = 0;

	while (i < size)
	{
		d = tab[i++];
		if (!flags.a && d->d_name[0] == '.')	{
			continue;
		}
		if (flags.l)	{
			stat(d->d_name, &st);
			print_mode(st.st_mode);
			printf("%ld\t", st.st_nlink);
			printf("%s\t", getpwuid(st.st_uid)->pw_name);
			printf("%s\t", getgrgid(st.st_gid)->gr_name);
			printf("%ld\t", st.st_size);
			print_time(st);
		}
		// if (flags.R)	{
		// 	printf("%s:", path);
		// }
		printf("%s\t", d->d_name);
		if (flags.l)
			printf("\n");
	}
}

void ft_ls(DIR *dh, flags_t flags)
{
	struct dirent	**tab;
	int				size;

	if (!dh)	{
		if (errno == ENOENT)
			perror("Directory does not exist");
		else
			perror("Unable to read directory");
		exit(EXIT_FAILURE);
	}

	tab = get_items(dh, &size, flags);	
	display(tab, size, flags);


	closedir(dh);
}

void set_flags_t(char *str, flags_t *flags)
{
	int i = 1;
	while (str[i]){
		if (str[i] == 'a')
			flags->a = 1;
		if (str[i] == 'l')
			flags->l = 1;
		if (str[i] == 'R')
			flags->R = 1;
		if (str[i] == 'r')
			flags->r = 1;
		if (str[i] == 't')
			flags->t = 1;
		i++;
	}
}

void disp_flags(flags_t *flags)
{
	printf("%d, %d, %d, %d, %d\n", flags->a, flags->l, flags->R, flags->r, flags->t);
}

int main(int ac, char **av){
	char *dir = ".";
	DIR *dh;
	flags_t flags = {0, 0, 0, 0, 0};

	if (ac == 1)	{
		dh = opendir(dir);
		ft_ls(dh, flags);
	}
	else	{
		int i = 1;
		while (i < ac){
			if (av[i][0] == '-'){
				set_flags_t(av[i], &flags);
			}
			else{
				dir = av[i];
			}
			i++;
		}
		dh = opendir(dir);
		ft_ls(dh, flags);
	}
	return 0;
}

