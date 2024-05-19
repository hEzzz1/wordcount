#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// ��������
long countCharacters(const char* filename);
long countWords(const char* filename);

int main(int argc, char* argv[]) {
    // ����������
    if (argc != 3) {
        printf("�÷���WordCount [-c|-w] <input_file_name>\n");
        return 1;
    }

    // ��ȡ����
    char* parameter = argv[1];
    char* inputFileName = argv[2];
    long count;

    // ���ݲ���ѡ��������ͳ��
    if (strcmp(parameter, "-c") == 0) {
        count = countCharacters(inputFileName);
        printf("�ַ�����%ld\n", count);
    }
    else if (strcmp(parameter, "-w") == 0) {
        count = countWords(inputFileName);
        printf("��������%ld\n", count);
    }
    else {
        printf("��Ч�Ĳ�����ʹ�� '-c' ͳ���ַ�����ʹ�� '-w' ͳ�Ƶ�������\n");
        return 1;
    }

    return 0;
}

// ͳ���ַ����ĺ���
long countCharacters(const char* filename) {
    FILE* file;
    long count = 0;
    errno_t err;
    char ch;

    // ʹ�� fopen_s ��ȫ���ļ�
    err = fopen_s(&file, filename, "r");
    if (err != 0) {
        perror("�޷����ļ�");
        exit(EXIT_FAILURE);
    }

    // ��ȡ�ַ�������
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }

    // �ر��ļ�
    fclose(file);
    return count;
}

// ͳ�Ƶ������ĺ���
long countWords(const char* filename) {
    FILE* file;
    long count = 0;
    errno_t err;
    char ch, last_ch = '\0';

    // ʹ�� fopen_s ��ȫ���ļ�
    err = fopen_s(&file, filename, "r");
    if (err != 0) {
        perror("�޷����ļ�");
        exit(EXIT_FAILURE);
    }

    // ��ȡ�ַ���ͳ�Ƶ�����
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

    // ����ļ����Էָ�����β�������һ��������Ҫ����
    if (last_ch != ' ' && last_ch != '\t' && last_ch != '\n' && last_ch != ',') {
        count++;
    }

    // �ر��ļ�
    fclose(file);
    return count;
}