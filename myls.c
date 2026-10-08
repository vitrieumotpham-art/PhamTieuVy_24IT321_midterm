#include "myls.h"

// Biến tĩnh (static) để truyền cấu hình cờ vào hàm qsort chuẩn
static LsOptions *current_opts = NULL;

// Thuật toán so sánh động dựa trên các cờ (Time, Size, Alphabetical)
int compare_files(const void *a, const void *b)
{
    FileInfo *f1 = (FileInfo *)a;
    FileInfo *f2 = (FileInfo *)b;
    int result = 0;

    if (current_opts->S)
    { // Cờ -S: Sắp xếp theo dung lượng
        result = (f2->st.st_size > f1->st.st_size) - (f2->st.st_size < f1->st.st_size);
    }
    else if (current_opts->t)
    { // Cờ -t: Sắp xếp theo thời gian
        time_t t1 = current_opts->u ? f1->st.st_atime : (current_opts->c ? f1->st.st_ctime : f1->st.st_mtime);
        time_t t2 = current_opts->u ? f2->st.st_atime : (current_opts->c ? f2->st.st_ctime : f2->st.st_mtime);
        result = (t2 > t1) - (t2 < t1);
    }

    if (result == 0)
    { // Mặc định: bảng chữ cái
        result = strcmp(f1->name, f2->name);
    }

    // Cờ -r: Đảo ngược kết quả
    return current_opts->r ? -result : result;
}

// Hàm in chi tiết file (Tích hợp -l, -n, -i, -s, -h, -F)
void print_long_format(FileInfo *file, LsOptions *opts)
{
    // 1. Cờ -i: In số Inode
    if (opts->i)
        printf("%7lu ", (unsigned long)file->st.st_ino);

    // 2. Cờ -s: In số blocks
    if (opts->s)
        printf("%4lld ", (long long)file->st.st_blocks / 2);

    // 3. Cờ -l hoặc -n: In phân quyền và thông tin chi tiết
    if (opts->l || opts->n)
    {
        printf(S_ISDIR(file->st.st_mode) ? "d" : "-");
        printf((file->st.st_mode & S_IRUSR) ? "r" : "-");
        printf((file->st.st_mode & S_IWUSR) ? "w" : "-");
        printf((file->st.st_mode & S_IXUSR) ? "x" : "-");
        printf((file->st.st_mode & S_IRGRP) ? "r" : "-");
        printf((file->st.st_mode & S_IWGRP) ? "w" : "-");
        printf((file->st.st_mode & S_IXGRP) ? "x" : "-");
        printf((file->st.st_mode & S_IROTH) ? "r" : "-");
        printf((file->st.st_mode & S_IWOTH) ? "w" : "-");
        printf((file->st.st_mode & S_IXOTH) ? "x" : "-");

        printf(" %2lu", (unsigned long)file->st.st_nlink);

        // Cờ -n: In UID/GID dạng số. Ngược lại in tên.
        if (opts->n)
        {
            printf(" %d %d", file->st.st_uid, file->st.st_gid);
        }
        else
        {
            struct passwd *pw = getpwuid(file->st.st_uid);
            struct group *gr = getgrgid(file->st.st_gid);
            printf(" %s %s", pw ? pw->pw_name : "unknown", gr ? gr->gr_name : "unknown");
        }

        // Cờ -h: In dung lượng dạng Human-readable (KB, MB)
        if (opts->h)
        {
            double size = file->st.st_size;
            const char *units[] = {"B", "K", "M", "G"};
            int u = 0;
            while (size > 1024 && u < 3)
            {
                size /= 1024;
                u++;
            }
            printf(" %4.1f%s", size, units[u]);
        }
        else
        {
            printf(" %5lld", (long long)file->st.st_size);
        }

        char time_buf[256];
        time_t time_val = opts->u ? file->st.st_atime : (opts->c ? file->st.st_ctime : file->st.st_mtime);
        struct tm *tm_info = localtime(&time_val);
        strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", tm_info);
        printf(" %s", time_buf);
    }

    // 4. Tên file
    printf(" %s", file->name);

    // 5. Cờ -F: Thêm ký tự đánh dấu loại file
    if (opts->F)
    {
        if (S_ISDIR(file->st.st_mode))
            printf("/");
        else if (file->st.st_mode & S_IXUSR)
            printf("*");
    }
    printf("\n");
}

void list_dir(const char *path, LsOptions *opts)
{
    // Cờ -d: Chỉ xử lý thông tin thư mục đó, không mở ra xem nội dung
    if (opts->d)
    {
        FileInfo dir_file;
        strncpy(dir_file.name, path, 255);
        if (stat(path, &dir_file.st) == 0)
            print_long_format(&dir_file, opts);
        return;
    }

    DIR *dir = opendir(path);
    if (!dir)
    {
        perror(path);
        return;
    }

    FileInfo *files = NULL;
    int count = 0, capacity = 10;
    files = malloc(capacity * sizeof(FileInfo));
    struct dirent *entry;

    // Quét file
    while ((entry = readdir(dir)) != NULL)
    {
        // Cờ -a, -A: Lọc file ẩn
        if (!opts->a && entry->d_name[0] == '.')
        {
            if (!opts->A)
                continue;
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
        }

        if (count >= capacity)
        {
            capacity *= 2;
            files = realloc(files, capacity * sizeof(FileInfo));
        }

        strncpy(files[count].name, entry->d_name, 255);
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        stat(full_path, &files[count].st);
        count++;
    }
    closedir(dir);

    // Sắp xếp bằng hàm qsort chuẩn C
    if (!opts->f)
    {
        current_opts = opts;
        qsort(files, count, sizeof(FileInfo), compare_files);
    }

    if (opts->R)
        printf("\n%s:\n", path);

    // In danh sách
    for (int i = 0; i < count; i++)
    {
        print_long_format(&files[i], opts);
    }

    // Đệ quy (-R)
    if (opts->R)
    {
        for (int i = 0; i < count; i++)
        {
            if (S_ISDIR(files[i].st.st_mode) && strcmp(files[i].name, ".") != 0 && strcmp(files[i].name, "..") != 0)
            {
                char next_path[1024];
                snprintf(next_path, sizeof(next_path), "%s/%s", path, files[i].name);
                list_dir(next_path, opts);
            }
        }
    }
    free(files);
}