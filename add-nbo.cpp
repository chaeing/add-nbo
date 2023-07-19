#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>

uint32_t file_open(const char* file_name) {
    FILE* pFile = fopen(file_name, "rb");
    if (pFile == NULL) {
        printf("파일을 열 수 없습니다: %s\n", file_name);
        return 0;
    }

    uint32_t temp;
    if (fread(&temp, sizeof(uint32_t), 1, pFile) != 1) {
        printf("파일을 읽지 못했습니다: %s\n", file_name);
        temp = 0;
    }

    fclose(pFile);
    temp = ntohl(temp);
    printf("%u(0x%x) ", temp, temp);
    return temp;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("사용법: %s <file1> [<file2> <file3> ...]\n", argv[0]);
        return 1;
    }

    uint32_t accumulate = 0;
    for (int i = 1; i < argc; i++) {
        accumulate += file_open(argv[i]);
        if (i < argc - 1) {
            printf(" + ");
        }
    }

    printf("= %u(0x%x)\n", accumulate, accumulate);
    return 0;
}
