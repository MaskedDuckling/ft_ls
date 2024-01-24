 #include "main.h"

char lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 'a' - 'A';
	return c;
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
