#include <stdio.h> //Библиотека за input output
#include <stdlib.h> //Библиотека за работа с файлове
#include <cs50.h> //Библиотека на cs50
#include <string.h> //Библиотека за използване на string-ове

typedef struct //Дефиниция на структура
{
    //Дефиниция на променливи, които ще запазват информация за ресурсите и тези които имат * са char променливи, които са pointer-и, за да може да се запазва информация в string
    int id;
    char *title;
    char *author;
    char *topic;
    char *url;
    char *description;
} Resource; //Име на структура

void add(); //Прототип на функцията за добавяне на ресурси
void listresources(); //Прототип на функцията за показване на ресурсите
void delete(); //Прототип за функцията за изтриване на ресурси
void update(); //Прототип за функцията за променяне на ресурси
void search(); //Прототип за функцията за намиране на ресурси

void add() //Функция за добавяне на ресурси
{
    Resource resource; //Инстанция към структурата, която пази данните за ресурсите
    FILE *file = fopen("resources.txt", "a"); //Отваряне на файла
    if (file == NULL) //Проверка за липсата на файла
    {
        printf("Файлът не може да се отвори\n"); //Ако файла липсва се отпечатва, че не може да се отвори файла
    }
    //Въвеждане на данни за ресурсите
    resource.id = get_int("Въведи ID: ");
    resource.title = get_string("Въведи заглавие: ");
    resource.author = get_string("Въведи автор: ");
    resource.topic = get_string("Въведи предмет: ");
    resource.url = get_string("Въведи URL: ");
    resource.description = get_string("Въведи описание: ");
    fprintf(file, "%d \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"\n",resource.id, resource.title, resource.author, resource.topic, resource.url, resource.description); //Записване на данните във файла с кавички за правилно запазване на стринговете с интервали
    fclose(file); //Затваряне на файла
}

void listresources() //Функция за показване на ресурсите
{
    Resource resource; //Инстанция към структурата, която пази данните за ресурсите
    FILE *file = fopen("resources.txt", "r"); //Отваряне на файла в режим на четене
    if (file == NULL) //Проверка за липсата на файла
    {
        printf("Файлът не може да се отвори\n"); //Ако файла липсва се отпечатва, че не може да се отвори файла
    }
    char title[256], author[256], topic[256], url[256], description[256];
    while (fscanf(file, "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\"",&resource.id, title, author, topic, url, description) != EOF) // Обхождане на файла и извеждане на информацията
    {
        printf("ID: %d\n", resource.id);
        printf("Заглавие: %s\n", title);
        printf("Автор: %s\n", author);
        printf("Предмет: %s\n", topic);
        printf("URL: %s\n", url);
        printf("Описание: %s\n", description);
        printf("\n");
    }
    fclose(file); //Затваряне на файла
}

void update() //Функция за променяне на ресурси
{
    Resource resource; //Инстанция към структурата, която пази данните за ресурсите
    int selectedid; //Променлива, която запазва въведеното ID от потребителя
    FILE *file = fopen("resources.txt", "r"); //Отваря файла, който пази данните
    FILE *tempfile = fopen("temp.txt", "w"); //Отваряне на файл, който е моментен
    if (file == NULL || tempfile == NULL) //Проверява дали тези два файла липсват
    {
        printf("Файловете не могат да се отворят\n"); //Ако тези файлове липсват се извежда, че тези файлове не могат да се отворят
    }
    selectedid = get_int("Въведи ID на ресурса, който искаш да промениш: "); //Въвеждане на ID на ресурса, който ще бъде променен
    char title[256], author[256], topic[256], url[256], description[256];
    while (fscanf(file, "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\"",&resource.id, title, author, topic, url, description) != EOF) // Обхождане на файла
    {
        if (resource.id == selectedid) //Проверява дали въведеното ID съвпада с вече съществуващо ID във файла и ако съвпада се въвеждат новите данни от потребителя
        {
            resource.title=get_string("Въведи ново заглавие: ");
            resource.author=get_string("Въведи нов автор: ");
            resource.topic=get_string("Въведи нов предмет: ");
            resource.url=get_string("Въведи ново URL: ");
            resource.description=get_string("Въведи ново описание: ");
        }
        fprintf(tempfile, "%d \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"\n",resource.id, resource.title, resource.author, resource.topic, resource.url, resource.description); //Записване на новите ресурси във файла
    }
    fclose(file); //Затваряне на главния файл
    fclose(tempfile); //Затваряне на моментния файл
    remove("resources.txt"); //Изтриване на главния файл
    rename("temp.txt", "resources.txt"); //Преименуване на моментния файл в името на главния, за да може да се запишат новите данни в него
}

void delete() //Функция за изтриване на ресурси
{
    Resource resource; //Инстанция към структурата, която пази данните за ресурсите
    FILE *file = fopen("resources.txt", "r"); //Отваря файла, който пази данните
    FILE *tempfile = fopen("tempfile.txt", "w"); //Отваряне на файл, който е моментен
    if (file == NULL || tempfile == NULL) //Проверка за липсата на файловете
    {
        printf("Файловете не могат да се отворят\n"); //Ако файловете не могат да се отворят
    }
    int selectedid = get_int("Въведи ID на ресурса, който искаш да изтриеш: "); //Въвеждане на ID на ресурса, който ще бъде изтрит
    char title[256], author[256], topic[256], url[256], description[256];
    while (fscanf(file, "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\"",&resource.id, title, author, topic, url, description) != EOF) // Четене на ресурси от файла и записване на всички, които не са с въведеното ID в временен файл
    {
        if (resource.id != selectedid) // Ако ID не съвпада с това за изтриване, записваме данните
        {
            fprintf(tempfile, "%d \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"\n",resource.id, title, author, topic, url, description);
        }
    }
    fclose(file); //Затваряне на главния файл
    fclose(tempfile); //Затваряне на временния файл
    remove("resources.txt"); //Изтриване на стария файл
    rename("tempfile.txt", "resources.txt"); //Преименуване на временния файл в главния
}

void search() //Функция за намиране на ресурси
{
    Resource resource; //Инстанция към структурата, която пази данните за ресурсите
    FILE *file = fopen("resources.txt", "r"); //Отваря файла, който пази данните
    if (file == NULL) //Проверка дали файлът може да се отвори
    {
        printf("Файлът не може да се отвори\n");
    }
    int selectedid = get_int("Въведи ID на ресурса, който искаш да намериш: "); //Въвеждане на ID на ресурса
    char title[256], author[256], topic[256], url[256], description[256];
    while (fscanf(file, "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\"",&resource.id, title, author, topic, url, description) != EOF) // Четене на ресурси от файла и показване на данните за намереното ID
    {
        if (resource.id == selectedid) // Ако ID съвпада, показваме информацията за ресурса
        {
            printf("ID: %d\n", resource.id);
            printf("Заглавие: %s\n", title);
            printf("Автор: %s\n", author);
            printf("Предмет: %s\n", topic);
            printf("URL: %s\n", url);
            printf("Описание: %s\n", description);
            printf("\n");
        }
    }
    fclose(file); //Затваряне на файла
}

int main() //Главната функция за изпълнение на програмата
{
    int choice; //Променлива, която ще пази опцията, която потребителя въведе
    do
    {
        printf("------------- Програма за управляване на ресурси -------------\n"); //Дизайн
        printf("1. Добавяне на ресурс \n"); //Упътване
        printf("2. Променяне на ресурс \n"); //Упътване
        printf("3. Изтриване на ресурс \n"); //Упътване
        printf("4. Показване на ресурси \n"); //Упътване
        printf("5. Търсене на ресурс \n"); //Упътване
        printf("\n"); //Отпечатване на нов ред
        choice = get_int("Избери опция (номер): "); //Въвеждане на опция от потребителя
        switch (choice)
        {
            case 1: add(); break; //Ако потребителя въведе 1 ще се изпълни функцията за добавяне на ресурси
            case 2: update(); break; //Ако потребителя въведе 2 ще се изпълни функцията за променяне на ресурси
            case 3: delete(); break; //Ако потребителя въведе 3 ще се изпълни функцията за изтриване на ресурси
            case 4: listresources(); break; //Ако потребителя въведе 4 ще се изпълни функцията за показване на ресурси
            case 5: search(); break; //Ако потребителя въведе 5 ще се изпълни функцията за намиране на ресурси
            default: printf("Невалидна опция \n"); //Ако се въведе нещо различно от изброените опции ще се изведе, че въведената опция от потребителя е невалидна
        }
    }
    while (choice != 0); //Програмата не спира да се изпълнява докато избора е различен от 0
}
