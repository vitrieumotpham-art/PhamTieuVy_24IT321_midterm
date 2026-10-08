#include "myls.h"

int main(int argc, char *argv[])
{
    LsOptions opts = {0}; // Khởi tạo tất cả các cờ bằng 0 (false)
    int opt;

    // Lắng nghe toàn bộ 19 cờ từ manual page
    while ((opt = getopt(argc, argv, "AacdFfhiklnqRrSstuw")) != -1)
    {
        switch (opt)
        {
        case 'A':
            opts.A = 1;
            break;
        case 'a':
            opts.a = 1;
            break;
        case 'c':
            opts.c = 1;
            break;
        case 'd':
            opts.d = 1;
            break;
        case 'F':
            opts.F = 1;
            break;
        case 'f':
            opts.f = 1;
            break;
        case 'h':
            opts.h = 1;
            break;
        case 'i':
            opts.i = 1;
            break;
        case 'k':
            opts.k = 1;
            break;
        case 'l':
            opts.l = 1;
            break;
        case 'n':
            opts.n = 1;
            break;
        case 'q':
            opts.q = 1;
            break;
        case 'R':
            opts.R = 1;
            break;
        case 'r':
            opts.r = 1;
            break;
        case 'S':
            opts.S = 1;
            break;
        case 's':
            opts.s = 1;
            break;
        case 't':
            opts.t = 1;
            break;
        case 'u':
            opts.u = 1;
            break;
        case 'w':
            opts.w = 1;
            break;
        default:
            fprintf(stderr, "Usage: %s [-AacdFfhiklnqRrSstuw] [file ...]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Nếu -f được bật, bỏ qua sắp xếp (tắt -t, -S, -r)
    if (opts.f)
    {
        opts.a = 1;
        opts.t = 0;
        opts.S = 0;
        opts.r = 0;
    }

    const char *path = ".";
    if (optind < argc)
    {
        path = argv[optind];
    }

    list_dir(path, &opts);
    return 0;
}