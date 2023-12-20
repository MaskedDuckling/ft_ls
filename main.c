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

typedef struct operator_t{
    int op_a;
    int op_l;
    int op_R;
    int op_r;
    int op_t;
} operator;

char *get_mode(mode_t mode){
    char *str = malloc(sizeof(char) * 11);
    printf("%d ", mode);
    str[0] = S_ISDIR(mode) ? 'd' : '-';
    str[1] = (mode & S_IRUSR) ? 'r' : '-';
    str[2] = (mode & S_IWUSR) ? 'w' : '-';
    str[3] = (mode & S_IXUSR) ? 'x' : '-';
    str[4] = (mode & S_IRGRP) ? 'r' : '-';
    str[5] = (mode & S_IWGRP) ? 'w' : '-';
    str[6] = (mode & S_IXGRP) ? 'x' : '-';
    str[7] = (mode & S_IROTH) ? 'r' : '-';
    str[8] = (mode & S_IWOTH) ? 'w' : '-';
    str[9] = (mode & S_IXOTH) ? 'x' : '-';
    str[10] = '\0';
    return str;
}

void get_time(struct stat st){
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

void ft_ls(const char *dir, operator op){
    struct dirent *d;
    DIR *dh = opendir(dir);
    struct stat st;
    if (!dh){
        if (errno == ENOENT){
            perror("Directory does not exist");
        }
        else{
            perror("Unable to read directory");
        }
        exit(EXIT_FAILURE);
    }
    while ((d = readdir(dh)) != NULL){
        if (!op.op_a && d->d_name[0] == '.'){
            continue;
        }
        if (op.op_l){
            stat(d->d_name, &st);
            printf("%s\t", S_ISDIR(st.st_mode) ? "d" : "-");
            printf("%s\t", get_mode(st.st_mode));
            printf("%ld\t", st.st_nlink);
            printf("%s\t", getpwuid(st.st_uid)->pw_name);
            printf("%s\t", getgrgid(st.st_gid)->gr_name);
            printf("%ld\t", st.st_size);
            get_time(st);

        }
        //tri ici
        printf("%s\t", d->d_name);
        if (op.op_l){
            printf("\n");
        }
    }
    if (!op.op_l)
        printf("\n");
    closedir(dh);
}

operator init_op(){
    operator op;
    op.op_a = 0;
    op.op_l = 0;
    op.op_R = 0;
    op.op_r = 0;
    op.op_t = 0;
    return op;
}

void set_operator(char *str, operator *op){
    int i = 1;
    while (str[i]){
        if (str[i] == 'a')
            op->op_a = 1;
        if (str[i] == 'l')
            op->op_l = 1;
        if (str[i] == 'R')
            op->op_R = 1;
        if (str[i] == 'r')
            op->op_r = 1;
        if (str[i] == 't')
            op->op_t = 1;
        i++;
    }
}

void disp_op(operator *op){
    printf("%d, %d, %d, %d, %d\n", op->op_a, op->op_l, op->op_R, op->op_r, op->op_t);
}

int main(int ac, char **av){
    char *dir = ".";
    operator op = init_op();
    if (ac == 1){
        ft_ls(".", op);
    }
    else{
        int i = 1;
        while (i < ac){
            if (av[i][0] == '-'){
                set_operator(av[i], &op);
            }
            else{
                dir = av[i];
            }
            i++;
        }
        ft_ls(dir, op);
    }
    return 0;
}