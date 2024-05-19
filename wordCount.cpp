#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// 函数声明
long countCharacters(const char* filename);
long countWords(const char* filename);

int main(int argc, char* argv[]) {
    // 检查参数数量
    if (argc != 3) {
        printf("用法：WordCount [-c|-w] <input_file_name>\n");
        return 1;
    }

    // 读取参数
    char* parameter = argv[1];
    char* inputFileName = argv[2];
    long count;

    // 根据参数选择函数进行统计
    if (strcmp(parameter, "-c") == 0) {
        count = countCharacters(inputFileName);
        printf("字符数：%ld\n", count);
    }
    else if (strcmp(parameter, "-w") == 0) {
        count = countWords(inputFileName);
        printf("单词数：%ld\n", count);
    }
    else {
        printf("无效的参数。使用 '-c' 统计字符数或使用 '-w' 统计单词数。\n");
        return 1;
    }

    return 0;
}

// 统计字符数的函数
long countCharacters(const char* filename) {
    FILE* file;
    long count = 0;
    errno_t err;
    char ch;

    // 使用 fopen_s 安全打开文件
    err = fopen_s(&file, filename, "r");
    if (err != 0) {
        perror("无法打开文件");
        exit(EXIT_FAILURE);
    }

    // 读取字符并计数
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }

    // 关闭文件
    fclose(file);
    return count;
}

// 统计单词数的函数
long countWords(const char* filename) {
    FILE* file;
    long count = 0;
    errno_t err;
    char ch, last_ch = '\0';

    // 使用 fopen_s 安全打开文件
    err = fopen_s(&file, filename, "r");
    if (err != 0) {
        perror("无法打开文件");
        exit(EXIT_FAILURE);
    }

    // 读取字符并统计单词数
    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == ',') {
            if (last_ch != ' ' && last_ch != '\t' && last_ch != '\n' && last_ch != ',') {
                count++;
            }
            last_ch = ch;
        }
        else {
            last_ch = ch;
        }
    }

    // 如果文件不以分隔符结尾，则最后一个单词需要计数
    if (last_ch != ' ' && last_ch != '\t' && last_ch != '\n' && last_ch != ',') {
        count++;
    }

    // 关闭文件
    fclose(file);
    return count;
}