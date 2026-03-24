#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

// Структура для хранения данных о заказе
struct TOrder {
    char name[100]; // Наименование заказа
    struct {
        int hours;
        int minutes;
        int seconds;
    } time;
};

// Функция для перевода строки в верхний регистр (Win1251)
char* ANSIUpperCase(char* s, char* S) {
    S = strcpy(S, s);
    char* ch = S;
    while (*ch) {
        if (*ch >= 'a' && *ch <= 'z' || *ch >= 'а' && *ch <= 'я') *ch = *ch - 32;
        if (*ch == 'ё') *ch = 'Ё';
        ch++;
    }
    return S;
}

// Создание двоичного файла из текстового
void CreateBinaryFile() {
    char textFileName[256];
    char binFileName[256];

    printf("Введите имя текстового файла: ");
    fgets(textFileName, sizeof(textFileName), stdin);
    textFileName[strcspn(textFileName, "\n")] = '\0';

    printf("Введите имя двоичного файла: ");
    fgets(binFileName, sizeof(binFileName), stdin);
    binFileName[strcspn(binFileName, "\n")] = '\0';

    FILE* ft = fopen(textFileName, "rt");
    if (ft == NULL) {
        printf("Error: не удалось открыть файл с исходными данными %s\n", textFileName);
        printf("Press any key ");
        getch();
        return;
    }

    // Проверка на пустой файл
    fseek(ft, 0, SEEK_END);
    long fileSize = ftell(ft);
    if (fileSize == 0) {
        fclose(ft);
        printf("Исходный файл пуст\n");
        printf("Press any key to continue");
        getch();
        return;
    }
    fseek(ft, 0, SEEK_SET);

    FILE* fb = fopen(binFileName, "wb");
    if (fb == NULL) {
        fclose(ft);
        printf("Error: не удалось создать двоичный файл %s\n", binFileName);
        printf("Press any key");
        getch();
        return;
    }

    TOrder order;
    int kol = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), ft)) {
        if (strcmp(buffer, "**\n") == 0 || feof(ft)) break;

        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(order.name, buffer, sizeof(order.name) - 1);
        order.name[sizeof(order.name) - 1] = '\0';

        if (fgets(buffer, sizeof(buffer), ft) == NULL) break;
        sscanf(buffer, "%d %d %d", &order.time.hours, &order.time.minutes, &order.time.seconds);

        fwrite(&order, sizeof(order), 1, fb);
        kol++;
    }

    fclose(ft);
    fclose(fb);

    if (kol == 0) {
        printf("Исходный файл не содержит корректных записей\n");
    }
    else {
        printf("Создан двоичный файл из %d записей\n", kol);
    }
    printf("Press any key to continue");
    getch();
}

// Поиск заказов по времени
void FindOrders() {
    char binFileName[256];

    printf("Введите имя двоичного файла: ");
    fgets(binFileName, sizeof(binFileName), stdin);
    binFileName[strcspn(binFileName, "\n")] = '\0';

    FILE* fb = fopen(binFileName, "rb");
    if (fb == NULL) {
        printf("Error: не удалось открыть двоичный файл %s\n", binFileName);
        printf("Press ENTER");
        getch();
        return;
    }

    TOrder order;
    int kol = 0;

    printf("Заказы с 15:20:35 до 18:50:10:\n");
    printf("%-50s %-10s\n", "Наименование заказа", "Время поступления");
    printf("------------------------------------------------------------\n");

    while (fread(&order, sizeof(order), 1, fb)) {
        int total_seconds = order.time.hours * 3600 + order.time.minutes * 60 + order.time.seconds;
        int start = 15 * 3600 + 20 * 60 + 35;
        int end = 18 * 3600 + 50 * 60 + 10;

        if (total_seconds >= start && total_seconds <= end) {
            printf("%-50s %02d:%02d:%02d\n", order.name, order.time.hours, order.time.minutes, order.time.seconds);
            kol++;
        }
    }

    if (kol == 0)
        printf("Данные, соответствующие запросу, не найдены\n");
    else
        printf("Всего найдено: %d\n", kol);

    fclose(fb);
    printf("Press any key to continue");
    getch();
}

// Корректировка данных в файле
void CorrectFile() {
    char binFileName[256];

    printf("Введите имя двоичного файла: ");
    fgets(binFileName, sizeof(binFileName), stdin);
    binFileName[strcspn(binFileName, "\n")] = '\0';

    FILE* fb = fopen(binFileName, "rb+");
    if (fb == NULL) {
        printf("Error: не удалось открыть двоичный файл %s\n", binFileName);
        printf("Press ENTER");
        getch();
        return;
    }

    TOrder order;
    int kol = 0;

    while (fread(&order, sizeof(order), 1, fb)) {
        int flag = 0;

        if (order.time.hours < 0) { order.time.hours = 0; flag = 1; }
        if (order.time.hours > 23) { order.time.hours = 23; flag = 1; }

        if (order.time.minutes < 0) { order.time.minutes = 0; flag = 1; }
        if (order.time.minutes > 59) { order.time.minutes = 59; flag = 1; }

        if (order.time.seconds < 0) { order.time.seconds = 0; flag = 1; }
        if (order.time.seconds > 59) { order.time.seconds = 59; flag = 1; }

        if (flag) {
            kol++;
            fseek(fb, -sizeof(order), SEEK_CUR);
            fwrite(&order, sizeof(order), 1, fb);
            fflush(fb);
            fseek(fb, 0, SEEK_CUR);
        }
    }

    if (kol == 0)
        printf("Ни одной корректировки\n");
    else
        printf("Всего корректировок: %d\n", kol);

    fclose(fb);
    printf("Press any key to continue");
    getch();
}

// Просмотр содержимого файла
void ViewBinaryFile() {
    char binFileName[256];

    printf("Введите имя двоичного файла: ");
    fgets(binFileName, sizeof(binFileName), stdin);
    binFileName[strcspn(binFileName, "\n")] = '\0';

    FILE* fb = fopen(binFileName, "rb");
    if (fb == NULL) {
        printf("Error: не удалось открыть двоичный файл %s\n", binFileName);
        printf("Press ENTER");
        getch();
        return;
    }

    TOrder order;
    int count = 0;

    printf("Содержимое файла:\n");
    printf("%-5s %-50s %-10s\n", "№", "Наименование заказа", "Время поступления");
    printf("------------------------------------------------------------\n");

    while (fread(&order, sizeof(order), 1, fb)) {
        count++;
        printf("%-5d %-50s %02d:%02d:%02d\n", count, order.name,
            order.time.hours, order.time.minutes, order.time.seconds);
    }

    if (count == 0)
        printf("Файл пуст\n");
    else
        printf("Всего записей: %d\n", count);

    fclose(fb);
    printf("Press any key to continue");
    getch();
}

// Главное меню
int main() {
    char ch;
    SetConsoleOutputCP(1251);

    do {
        printf("\nМеню:\n");
        printf("N - создать двоичный файл из текстового\n");
        printf("F - поиск заказов по времени\n");
        printf("C - корректировка данных в файле\n");
        printf("V - просмотр содержимого файла\n");
        printf("E - выход\n");
        printf("Ваш выбор? ");

        ch = getchar();
        fflush(stdin);
        ch = toupper(ch);

        switch (ch) {
        case 'N': CreateBinaryFile(); break;
        case 'F': FindOrders(); break;
        case 'C': CorrectFile(); break;
        case 'V': ViewBinaryFile(); break;
        case 'E': return 0;
        default:
            printf("Нет такой команды\nPress any key");
            getch();
        }
    } while (ch != 'E');

    return 0;
}