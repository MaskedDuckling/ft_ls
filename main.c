#include "main.h"

struct dirent **get_items(DIR *dh, int *size, flags_t flags)
{
	struct dirent **tab = malloc(sizeof(struct dirent*) * 100);
	struct dirent *d;
	int i = 0;

	while ((d = readdir(dh)) != NULL)	{
		if (!flags.a && d->d_name[0] == '.')	{
			continue;
		}
		tab[i++] = d;
	}
	*size = i;

	if (flags.t)
		sort_tab(tab, *size, flags.r, time_compare);
	else
		sort_tab(tab, *size, flags.r, name_compare);

	return tab;
}

void display(struct dirent **tab, int size, flags_t flags)
{
	struct stat		st;
	struct dirent	*d;
	int 			i = 0;
	char buf[1024];

	while (i < size)
	{
		d = tab[i++];
		stat(d->d_name, &st);
		if (flags.l)	{
			print_mode(st.st_mode, d->d_type);
			printf("%ld\t", st.st_nlink);
			printf("%s\t", getpwuid(st.st_uid)->pw_name);
			printf("%s\t", getgrgid(st.st_gid)->gr_name);
			printf("%ld\t", st.st_size);
			print_time(st);
		}

		printf("%s\t", d->d_name);

		if (flags.l){
			if (d->d_type == DT_LNK){
				int k = readlink(d->d_name , buf, 1024);
				if (k > 0)
					buf[k] = '\0';
					printf(" -> %s",buf);
				k = 0;
			}	
		}
		if(flags.l)
			printf("\n");
	}
	if(!flags.l)
		printf("\n");
}

void ft_ls(char *path, flags_t flags)
{
	struct dirent	**tab;
	int				size;
	DIR				*dh;

	char *join = ft_strjoin(path, "/");
	char *join2;
	

	dh = opendir(path);
	if (!dh)	{
		if (errno == ENOENT)
			perror("Directory does not exist");
		else
			perror("Unable to read directory");
		exit(EXIT_FAILURE);
	}

	tab = get_items(dh, &size, flags);
	display(tab, size, flags);
	
	if (flags.R)
	{
		struct dirent *d;
		int i = 0;
		while (i < size)
		{
			d = tab[i++];
			if (d->d_type == DT_DIR && ft_strcmp(d->d_name, ".") && ft_strcmp(d->d_name, ".."))
			{
				join2 = ft_strjoin(join, d->d_name);
				printf("\n%s:\n", join2);
				ft_ls(join2, flags);
				free(join2);
			}
		}
	}

	closedir(dh);
	free(join);
	free(tab);
}

int main(int ac, char **av){
	char *path = ".";
	flags_t flags = {0, 0, 0, 0, 0};

	int i = 1;
	while (i < ac){
		if (av[i][0] == '-'){
			set_flags_t(av[i], &flags);
		}
		else{
			path = av[i];
		}
		i++;
	}
	if (flags.R)
		printf("%s:\n", path);

	ft_ls(path, flags);
	return 0;
}

