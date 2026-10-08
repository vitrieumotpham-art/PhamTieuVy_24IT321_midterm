#ifndef MYLS_H
#define MYLS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

// Struct lưu trữ trạng thái của 19 cờ (flags) theo yêu cầu đề bài
typedef struct
{
    int A, a, c, d, F, f, h, i, k, l, n, q, R, r, S, s, t, u, w;
} LsOptions;

// Cấu trúc gom nhóm tên và thông tin file để sắp xếp
typedef struct
{
    char name[256];
    struct stat st;
} FileInfo;

// Khai báo hàm chính xử lý thư mục
void list_dir(const char *path, LsOptions *opts);

#endif