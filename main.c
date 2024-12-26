#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/limits.h>

int flag = 0;

int get_depth(const char *path, char *deepest_dir) {
    if(flag) printf("path: %s\n", path);
    DIR *dir;
    struct dirent *entry;
    int max_depth = 0;

    if (!(dir = opendir(path))) {
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
        char new_path[PATH_MAX];
        struct stat statbuf;
        int depth;

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
        if (lstat(new_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode) && !S_ISLNK(statbuf.st_mode)) {
            char temp_deepest_dir[PATH_MAX];
            depth = get_depth(new_path, temp_deepest_dir);

            if (depth > max_depth) {
                max_depth = depth;
                strcpy(deepest_dir, temp_deepest_dir);
            }
        }
    }

    closedir(dir);
    if (max_depth == 0) {
        strcpy(deepest_dir, path);
    }
    return max_depth + 1;
}

int main(int argc, char *argv[]) {
    flag = (argc > 1 && strcmp(argv[1], "--verbose") == 0) ? 1 : 0;
    char cwd[PATH_MAX];
    char deepest_dir[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return 1;
    }

    int depth = get_depth(cwd, deepest_dir);
    printf("Depth of the filesystem tree from the current directory: %d\n", depth);
    printf("Deepest directory: %s\n", deepest_dir);

    return 0;
}
