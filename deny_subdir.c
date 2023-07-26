#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
/**
 *deny_sub - change permission
 *Return nothing
 */


void deny_sub(void)
{
DIR *dir;
struct dirent *entry;
struct stat fileStat;

dir = opendir(".");
if (dir == NULL)
{
perror("Unable to open directory");
return;
}

while ((entry = readdir(dir)) != NULL)
{
if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
{
char folderPath[512];
snprintf(folderPath, sizeof(folderPath), "./%s", entry->d_name);

if (stat(folderPath, &fileStat) < 0)
{
perror("Unable to get file stat");
continue;
}

if (chmod(folderPath, fileStat.st_mode & ~S_IRUSR) < 0)
{
perror("Unable to remove read access");
}
else
{
printf("Read access removed for folder: %s\n", folderPath);
}

}
}

closedir(dir);
}
