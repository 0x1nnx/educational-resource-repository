#include <stdio.h>  // Библиотека за вход/изход
#include <stdlib.h> // Библиотека за работа с файлове
#include <string.h> // Библиотека за работа със стрингове

// Дефиниция на структура
typedef struct {
    int id;
    char title[256];
    char author[256];
    char topic[256];
    char url[256];
    char description[256];
} Resource;

void add(); //Прототип на функцията за добавяне на ресурси
void listresources(); //Прототип на функцията за показване на ресурсите
void delete(); //Прототип за функцията за изтриване на ресурси
void update(); //Прототип за функцията за променяне на ресурси
void search(); //Прототип за функцията за намиране на ресурси

void add() //Функция за добавяне на ресурс
{
    Resource resource; //Инстанция към структурата, която пази данните за ресурсите
    FILE *file = fopen("resources.txt", "a"); //Отваряне на файла
    if (file == NULL) //Проверка за липсата на файла
    {
        printf("Файлът не може да се отвори\n"); //Ако файла липсва се отпечатва, че не може да се отвори файла
    }
    //Въвеждане на информация за ресурсите
    printf("Въведи ID: ");
    scanf("%d", &resource.id);
    getchar();
    printf("Въведи заглавие: ");
    fgets(resource.title, sizeof(resource.title), stdin);
    resource.title[strcspn(resource.title, "\n")] = '\0';
    printf("Въведи автор: ");
    fgets(resource.author, sizeof(resource.author), stdin);
    resource.author[strcspn(resource.author, "\n")] = '\0';
    printf("Въведи предмет: ");
    fgets(resource.topic, sizeof(resource.topic), stdin);
    resource.topic[strcspn(resource.topic, "\n")] = '\0';
    printf("Въведи URL: ");
    fgets(resource.url, sizeof(resource.url), stdin);
    resource.url[strcspn(resource.url, "\n")] = '\0';
    printf("Въведи описание: ");
    fgets(resource.description, sizeof(resource.description), stdin);
    resource.description[strcspn(resource.description, "\n")] = '\0';
    fprintf(file, "%d \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"\n",resource.id, resource.title, resource.author, resource.topic, resource.url, resource.description); //Записване на ресурсите във файла
    fclose(file); //Затваряне на файла
}

void listresources() //Функция за показване на ресурсите
{
    Resource resource; //Инстанция към структурата, която пази данните за ресурсите
    FILE *file = fopen("resources.txt", "r"); //Отваряне на файла
    if (file == NULL) //Проверка за липсата на файла
    {
        printf("Файлът не може да се отвори\n"); //Ако файла липсва се отпечатва, че не може да се отвори файла
    }
    while (fscanf(file, "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\"",&resource.id, resource.title, resource.author, resource.topic, resource.url, resource.description) != EOF) //Обхождане на елементите от файла
    {
        //Извеждане на ресурсите
        printf("ID: %d\n", resource.id);
        printf("Заглавие: %s\n", resource.title);
        printf("Автор: %s\n", resource.author);
        printf("Предмет: %s\n", resource.topic);
        printf("URL: %s\n", resource.url);
        printf("Описание: %s\n", resource.description);
        printf("\n");
    }
    fclose(file); //Затваряне на файла
}

void delete() //Функция за изтриване на ресурс
{
    Resource resource; //Инстанция към структурата, която пази данните за ресурсите
    FILE *file = fopen("resources.txt", "r"); //Отваряне на файла
    FILE *tempfile = fopen("tempfile.txt", "w"); //Създава се временен файл
    if (file == NULL || tempfile == NULL) //Проверка за липсата на файловете
    {
        printf("Файловете не могат да се отворят\n"); //Ако файловете липсват се извежда, че не могат да се отворят
    }
    int selectedid;
    //Въвеждане на ID на ресурса, който искаме да изтрием
    printf("Въведи ID на ресурса, който искаш да изтриеш: ");
    scanf("%d", &selectedid);
    getchar(); // Почистваме буфера
    while (fscanf(file, "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\"",&resource.id, resource.title, resource.author, resource.topic, resource.url, resource.description) != EOF) //Обхождане на елементите от файла
    {
        if (resource.id != selectedid) //Ако въведеното ID е различно от ID на елемента, който искаме да изтрием се записват само тези файлове, които са с различно ID, за да можем това което искаме да се изтрие
        {
            fprintf(tempfile, "%d \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"\n",resource.id, resource.title, resource.author, resource.topic, resource.url, resource.description);
        }
    }
    fclose(file); //Затваряне на главния файл
    fclose(tempfile); //Затваряне на временния файл
    remove("resources.txt"); //Изтриване на главния файл
    rename("tempfile.txt", "resources.txt"); //Преименуване на временния файл в името на главния, за да може той да играе функцията на главния файл, който съхранява ресурсите
}

void update() //Функция за промяна на ресурс
{
    Resource resource; //Инстанция към структурата, която пази данните за ресурсите
    int selectedid;
    FILE *file = fopen("resources.txt", "r"); //Отваряне на файла
    FILE *tempfile = fopen("temp.txt", "w"); //Създава се временен файл
    if (file == NULL || tempfile == NULL) //Проверка за липсата на фвата файла
    {
        printf("Файловете не могат да се отворят\n"); //Ако файловете липсват се извежда , че не могат да се отворят
    }
    //Въвеждане на ID на ресурса, който искаме да променим
    printf("Въведи ID на ресурса, който искаш да промениш: ");
    scanf("%d", &selectedid);
    getchar(); // Почистваме буфера
    while (fscanf(file, "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\"",&resource.id, resource.title, resource.author, resource.topic, resource.url, resource.description) != EOF) //Обхождане на файла
    {
        if (resource.id == selectedid) //Ако въведеното ID съвпада със съществуващо такова във файла се започва процеса за промяна на данните на този ресурс
         {
            //Въвеждане на нови данни за ресурса
            printf("Въведи ново заглавие: ");
            fgets(resource.title, sizeof(resource.title), stdin);
            resource.title[strcspn(resource.title, "\n")] = '\0';
            printf("Въведи нов автор: ");
            fgets(resource.author, sizeof(resource.author), stdin);
            resource.author[strcspn(resource.author, "\n")] = '\0';
            printf("Въведи нов предмет: ");
            fgets(resource.topic, sizeof(resource.topic), stdin);
            resource.topic[strcspn(resource.topic, "\n")] = '\0';
            printf("Въведи ново URL: ");
            fgets(resource.url, sizeof(resource.url), stdin);
            resource.url[strcspn(resource.url, "\n")] = '\0';
            printf("Въведи ново описание: ");
            fgets(resource.description, sizeof(resource.description), stdin);
            resource.description[strcspn(resource.description, "\n")] = '\0';
        }
        fprintf(tempfile, "%d \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"\n",resource.id, resource.title, resource.author, resource.topic, resource.url, resource.description); //Записване на данните във временния файл
    }
    fclose(file); //Затваряне на главния файл
    fclose(tempfile); //Затваряне на временния файл
    remove("resources.txt"); //Изтриване на главния файл
    rename("temp.txt", "resources.txt"); //Преименуване на временния файл в името на главния, за да може той да играе функцията на главния файл, който съхранява ресурсите
}

void search() //Функция за търсене на ресурс
{
    Resource resource; //Инстанция към структурата, която пази данните за ресурсите
    FILE *file = fopen("resources.txt", "r"); //Отваряне на файла
    if (file == NULL) //Проверка за липсата на файла
    {
        printf("Файлът не може да се отвори\n"); //Ако файла не същестува не може да се отвори
    }
    int selectedid;
    //Въвеждане на ID на ресурса, който искаме да намерим
    printf("Въведи ID на ресурса, който искаш да намериш: ");
    scanf("%d", &selectedid);
    getchar(); // Почистваме буфера
    while (fscanf(file, "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\"",&resource.id, resource.title, resource.author, resource.topic, resource.url, resource.description) != EOF) //Обхождане на файла
    {
        if (resource.id == selectedid) //Ако въведеното ID съвпада с вече съществуващо такова във файла се извежда ресурса с това ID
        {
            //Извеждане на ресурса, който търсим
            printf("ID: %d\n", resource.id);
            printf("Заглавие: %s\n", resource.title);
            printf("Автор: %s\n", resource.author);
            printf("Предмет: %s\n", resource.topic);
            printf("URL: %s\n", resource.url);
            printf("Описание: %s\n", resource.description);
            printf("\n");
        }
    }
    fclose(file); //Затваряне на файла
}

int main() //Главна функция
{
    int choice; //Променлива, която съхранява опцията, която ще изберем
    do
    {
        printf("------------- Програма за управляване на ресурси -------------\n"); //Дизайн
        //Инструкции
        printf("1. Добавяне на ресурс\n");
        printf("2. Променяне на ресурс\n");
        printf("3. Изтриване на ресурс\n");
        printf("4. Показване на ресурси\n");
        printf("5. Търсене на ресурс\n");
        printf("\n"); // Нов ред
        //Въвеждане на опцията
        printf("Избери опция (номер): ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
            case 1: add(); break; //Ако се избере първата опция ще се изпълни функцията за добавяне на ресурси
            case 2: update(); break; //Ако се избере втората опция ще се изпълни функцията за променяне на ресурс
            case 3: delete(); break; //Ако се избере третата опция ще се изпълни функцията за изтриване на ресурс
            case 4: listresources(); break; //Ако се избере четвъртата опция ще се изпълни функцията за показване на ресурсите
            case 5: search(); break; //Ако се избере петата опция ще се изпълни функцията за търсене на ресурс
            default: printf("Невалидна опция\n"); //Ако се въведе число, което е различно от предложените функции ще се изведе, че това е невалидна опция
        }
    }
    while (choice != 0); //Програмата ще се изпълнява докато избора на опция е различен от 0
}
