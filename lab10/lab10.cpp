// Подключение необходимых заголовочных файлов
#include <windows.h>   // Для функций SetConsoleOutputCP и SetConsoleCP
#include <stdio.h>     // Стандартный ввод-вывод (printf, fgets, fopen и др.)
#include <conio.h>     // Для getch()
#include <string.h>    // Для работы со строками (strcspn и др.)
#include <ctype.h>     // Для isalpha() - проверки на латинские буквы

//---------------------------------------------------------------------------
// Структура для хранения информации об элементе стека
struct TInfo {
    char Symbol;       // Символ, который хранится в элементе стека
};

// Структура элемента стека (узла связного списка)
struct TElem {
    TInfo Info;        // Данные элемента (символ)
    TElem* Next;       // Указатель на следующий элемент стека
};

//-----------------------Прототипы функций------------------------------------
// (Объявления функций перед их использованием)

// Добавляет элемент в стек
TElem* PushStack(TElem* St, TInfo Info);

// Извлекает элемент из стека
TInfo PopStack(TElem** PSt);

// Перемещает верхний элемент из одного стека в другой
void TopToTop(TElem** PSt1, TElem** PSt2);

// Создает стек из файла
TElem* CreateStackFromFile(TElem* St);

// Создает стек с ручным вводом данных
TElem* CreateStackFromInput(TElem* St);

// Выводит содержимое стека на экран
void OutputStack(TElem* St);

// Решает задачу - создает два новых стека из исходного
void SolveTask(TElem* SourceStack, TElem** LatinStack, TElem** OtherStack);

// Освобождает память, занятую стеком
TElem* FreeStack(TElem* St);

// Сохраняет содержимое стека в файл
void SaveStackToFile(TElem* St, const char* filename);

//---------------------------------------------------------------------------
// Главная функция программы
int main() {
    // Указатели на вершины стеков:
    TElem* SourceStack = NULL;  // Исходный стек
    TElem* LatinStack = NULL;   // Стек для латинских букв (удвоенных)
    TElem* OtherStack = NULL;   // Стек для остальных символов
    
    char ch;  // Переменная для хранения выбора пользователя
    
    // Устанавливаем кодировку консоли для корректного отображения русских букв
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    // Основной цикл программы
    do {
        // Вывод меню
        printf("\n1 - создать стек из файла");
        printf("\n2 - создать стек вручную");
        printf("\n3 - вывод стеков на экран");
        printf("\n4 - сохранить стеки в файлы");
        printf("\n5 - решение задачи");
        printf("\n6 - освободить память");
        printf("\n0 - выход");
        printf("\nВаш выбор? ");
        
        // Получаем выбор пользователя
        ch = getchar(); 
        fflush(stdin);  // Очищаем буфер ввода

        // Обработка выбора пользователя
        switch (ch) {
        case '1':  // Создание стека из файла
            if (SourceStack) {
                printf("Error: сначала надо освободить память!");
                break;
            }
            SourceStack = CreateStackFromFile(SourceStack);
            break;

        case '2':  // Создание стека вручную
            if (SourceStack) {
                printf("Error: сначала надо освободить память!");
                break;
            }
            SourceStack = CreateStackFromInput(SourceStack);
            break;

        case '3':  // Вывод стеков
            printf("\nИсходный стек:\n");
            OutputStack(SourceStack);
            printf("\nСтек с латинскими буквами (удвоенными):\n");
            OutputStack(LatinStack);
            printf("\nСтек с остальными символами:\n");
            OutputStack(OtherStack);
            break;

        case '4':  // Сохранение в файлы
            SaveStackToFile(SourceStack, "source_stack.txt");
            SaveStackToFile(LatinStack, "latin_stack.txt");
            SaveStackToFile(OtherStack, "other_stack.txt");
            printf("Стеки сохранены в файлы: source_stack.txt, latin_stack.txt, other_stack.txt\n");
            break;

        case '5':  // Решение задачи
            LatinStack = FreeStack(LatinStack);
            OtherStack = FreeStack(OtherStack);
            SolveTask(SourceStack, &LatinStack, &OtherStack);
            printf("Задача решена: созданы два новых стека\n");
            break;

        case '6':  // Очистка памяти
            SourceStack = FreeStack(SourceStack);
            LatinStack = FreeStack(LatinStack);
            OtherStack = FreeStack(OtherStack);
            printf("Вся память под стеки освобождена\n");
            break;

        case '0':  // Выход
            // Освобождаем память перед выходом
            SourceStack = FreeStack(SourceStack);
            LatinStack = FreeStack(LatinStack);
            OtherStack = FreeStack(OtherStack);
            return 0;

        default:  // Неверный ввод
            printf("Нет такой команды\n");
        }
        
        // Пауза перед очисткой экрана
        printf("Press any key to continue");
        getch();
        system("cls");  // Очистка экрана консоли

    } while (ch != '0');

    return 0;
}

//---------------------------------------------------------------------------
// Реализация функций

// Функция добавления элемента в стек
// Принимает: St - указатель на вершину стека, Info - данные для добавления
// Возвращает: указатель на новую вершину стека
TElem* PushStack(TElem* St, TInfo Info) {
    // Создаем новый элемент
    TElem* Elem = new TElem;
    // Заполняем его данные
    Elem->Info = Info;
    // Новый элемент указывает на предыдущую вершину стека
    Elem->Next = St;
    // Возвращаем указатель на новый элемент (новую вершину)
    return Elem;
}

// Функция извлечения элемента из стека
// Принимает: PSt - указатель на указатель вершины стека
// Возвращает: данные извлеченного элемента
TInfo PopStack(TElem** PSt) {
    // Запоминаем текущий верхний элемент
    TElem* Elem = *PSt;
    // Сохраняем его данные
    TInfo Info = Elem->Info;
    // Перемещаем вершину на следующий элемент
    *PSt = Elem->Next;
    // Удаляем извлеченный элемент
    delete Elem;
    // Возвращаем данные
    return Info;
}

// Перемещение верхнего элемента из одного стека в другой
// Принимает: PSt1 - указатель на указатель вершины первого стека (откуда берем)
//            PSt2 - указатель на указатель вершины второго стека (куда кладем)
void TopToTop(TElem** PSt1, TElem** PSt2) {
    // Запоминаем верхний элемент первого стека
    TElem* Elem = *PSt1;
    if (Elem == NULL) return;  // Если стек пуст, ничего не делаем
    
    // Перемещаем вершину первого стека на следующий элемент
    *PSt1 = (*PSt1)->Next;
    // Верхний элемент теперь указывает на вершину второго стека
    Elem->Next = *PSt2;
    // Второй стек теперь начинается с этого элемента
    *PSt2 = Elem;
}

// Создание стека из файла
TElem* CreateStackFromFile(TElem* St) {
    char filename[256];  // Буфер для имени файла
    printf("Введите имя файла: ");
    fgets(filename, 255, stdin);  // Читаем имя файла
    // Удаляем символ новой строки из имени файла
    filename[strcspn(filename, "\n")] = '\0';

    // Открываем файл для чтения
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка открытия файла\n");
        return St;
    }

    TInfo Info;  // Переменная для хранения данных элемента
    int kol = 0; // Счетчик элементов
    char ch;     // Переменная для чтения символов из файла

    // Читаем файл посимвольно
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n' || ch == ' ') continue;  // Пропускаем пробелы и переносы
        
        // Заполняем данные элемента
        Info.Symbol = ch;
        // Добавляем элемент в стек
        St = PushStack(St, Info);
        kol++;  // Увеличиваем счетчик
    }

    fclose(file);  // Закрываем файл
    printf("Создан стек из %d элементов\n", kol);
    return St;
}

// Создание стека с ручным вводом
TElem* CreateStackFromInput(TElem* St) {
    TInfo Info;        // Данные элемента
    int kol = 0;       // Счетчик элементов
    char input[256];   // Буфер для ввода

    while (1) {
        printf("Введите символ (или * для завершения): ");
        fgets(input, 255, stdin);  // Читаем ввод пользователя
        
        // Проверяем на условие завершения ввода
        if (input[0] == '*' && (input[1] == '\n' || input[1] == '\0')) break;

        if (input[0] != '\n') {  // Игнорируем пустой ввод
            Info.Symbol = input[0];  // Запоминаем символ
            St = PushStack(St, Info);  // Добавляем в стек
            kol++;  // Увеличиваем счетчик
        }
    }

    printf("Создан стек из %d элементов\n", kol);
    return St;
}

// Вывод стека на экран
void OutputStack(TElem* St) {
    if (!St) {  // Если стек пуст
        printf("пустой\n");
        return;
    }

    // Создаем временный стек для правильного порядка вывода
    TElem* tempStack = NULL;
    TElem* current = St;
    
    // Переворачиваем стек, перемещая элементы во временный стек
    while (current) {
        TopToTop(&current, &tempStack);
    }
    
    // Выводим элементы и одновременно восстанавливаем исходный стек
    current = tempStack;
    while (current) {
        printf("%c ", current->Info.Symbol);  // Выводим символ
        TopToTop(&current, &St);  // Возвращаем элемент в исходный стек
    }
    printf("\n");
}

// Решение задачи - разделение исходного стека на два новых
void SolveTask(TElem* SourceStack, TElem** LatinStack, TElem** OtherStack) {
    TElem* current = SourceStack;  // Начинаем с вершины исходного стека
    
    while (current) {
        TInfo Info = current->Info;  // Получаем данные текущего элемента
        
        if (isalpha(Info.Symbol)) {  // Если это латинская буква
            // Добавляем в стек латинских букв ДВАЖДЫ
            *LatinStack = PushStack(*LatinStack, Info);
            *LatinStack = PushStack(*LatinStack, Info);
        } else {
            // Добавляем в стек других символов
            *OtherStack = PushStack(*OtherStack, Info);
        }
        
        current = current->Next;  // Переходим к следующему элементу
    }
}

// Освобождение памяти стека
TElem* FreeStack(TElem* St) {
    while (St) {  // Пока стек не пуст
        TElem* temp = St;  // Запоминаем текущий элемент
        St = St->Next;     // Переходим к следующему
        delete temp;       // Удаляем текущий элемент
    }
    return NULL;  // Возвращаем NULL (пустой стек)
}

// Сохранение стека в файл
void SaveStackToFile(TElem* St, const char* filename) {
    // Открываем файл для записи
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка открытия файла %s\n", filename);
        return;
    }

    // Создаем временный стек для правильного порядка сохранения
    TElem* tempStack = NULL;
    TElem* current = St;
    
    // Переворачиваем стек
    while (current) {
        TopToTop(&current, &tempStack);
    }
    
    // Сохраняем элементы из временного стека в файл
    current = tempStack;
    while (current) {
        fprintf(file, "%c\n", current->Info.Symbol);  // Записываем символ в файл
        current = current->Next;  // Переходим к следующему
    }

    fclose(file);  // Закрываем файл
}