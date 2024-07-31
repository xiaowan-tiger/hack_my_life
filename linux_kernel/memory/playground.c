#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>


void virtual_addr_demo(void) {
    int *ptr = (int *)malloc(sizeof(int) * 10); // 分配10个整数的内存
    if (ptr == NULL) {
        perror("malloc");
    }

    for (int i = 0; i < 11; i++) {
        ptr[i] = i;
        printf("ptr[%d] = %d (Virtual Address: %p)\n", i, ptr[i], (void *)&ptr[i]);
    }

    free(ptr); // 释放内存
}

void mmap_demo() {
    int fd;
    char *map;

    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    map = mmap(NULL, 4096, PROT_READ, MAP_PRIVATE, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("File content:\n%s\n", map);

    munmap(map, 4096);
    close(fd);

}


int main() {
    virtual_addr_demo();
    mmap_demo();
    return 1;
}

