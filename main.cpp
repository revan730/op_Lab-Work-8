#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>

using namespace std;

FILE *in,*out;
char s[1000];
int open_files();
void write_to_file();
void find_and_write_longest();
void write_count(int);
void print_content();
void close_files();

int main() {
    if (open_files() == 0)
        printf("Ошибка при открытии файлов");
    else
    {
        write_to_file();
        find_and_write_longest();
        print_content();
        close_files();
    }
    return 0;
}

int open_files()
{
    char a;
    cout << "Дополнить входящий файл или создать новый?(Y/N)";
    cin >> a;
    if (a == 'Y' || a == 'y')
        in = fopen("in","a+");
    else in = fopen("in","w+");
    cout << "Дополнить выходящий или создать новый?(Y/N)";
    cin >> a;
    if (a == 'Y' || a == 'y')
    out = fopen("out","a+");
    else out = fopen("out","w+");
    if (in != NULL && out != NULL)
        return 1;
    else
        return 0;
}

void find_and_write_longest()
{
    int longest_count = 0;
    rewind(in);
    while (fgets(s,1000,in) != NULL)//Читаем строку из файла,пока не достигнем EOF
    {
        int count = 0, m_index = 0;//Количество слов в строке,индекс самого длинного слова в массиве слов
        char words[100][100];
        cout << s;
        char *p = strtok(s, " .,\n");
        while (p != NULL)//Делим строку на слова
        {
            strcpy(words[count], p);
            p = strtok(NULL, " .,\n");
            count++;
        }
        for (int i = 0; i < count; i++)//находим самое длинное
        {
            if (strlen(words[i]) > strlen(words[i - 1]))
                m_index = i;
        }
        if (strlen(words[m_index]) > 0) {
        printf("Самое длинное слово - %s\n", words[m_index]);
        longest_count++;
        fputs(words[m_index], out);
        fputs("\n", out);
        }
    }
    write_count(longest_count);
}

void write_count(int c)
{
    fprintf(out,"%d\n",c);
}

void write_to_file(){
    char s[1000];
    while (fgets(s,1000,stdin) != NULL &&  s[0] != '\7')
    {
        fputs(s,in);
        fflush(in);
    }
}

void print_content()
{
    char str[100];
    rewind(out);
    cout << "Содержимое выходящего файла:\n";
    while (fgets(str,100,out) != NULL)
        cout << str;
}

void close_files()
{
    fclose(in);
    fclose(out);
}
