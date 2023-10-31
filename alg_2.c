#include <stdio.h>
#include <locale.h >

struct Students {
    char* name;
    char* surname;
    char* patronymic;
    int math;
    int physics;
    int informatics;
    struct Students* next;
};

struct Groups {
    int Number;
    struct Students* Student;
};

struct Groups Dekanat[5];

char* randomName() {
    char* names[] = { "Иван", "Никита", "Александр", "Лев", "Михаил", "Владимир", "Дмитрий", "Григорий", "Николай", "Олег" };
    return names[rand() % 10];
}

// Функция для генерации случайных фамилий на русском языке
char* randomSurname() {
    char* surnames[] = { "Иванов", "Смирнов", "Кузнецов", "Попов", "Васильев", "Петров", "Соколов", "Михайлов", "Новиков", "Федоров" };
    return surnames[rand() % 10];
}

// Функция для генерации случайных отчеств на русском языке
char* randomPatronymic() {
    char* patronymics[] = { "Иванович", "Петрович", "Александрович", "Дмитриевич", "Сергеевич", "Андреевич", "Владимирович", "Аркадьевич", "Геннадьевич", "Николаевич" };
    return patronymics[rand() % 10];
}

struct Students* createStudent() {
    struct Students* student = malloc(sizeof(struct Students));
    student->name = strdup(randomName());
    student->surname = strdup(randomSurname());
    student->patronymic = strdup(randomPatronymic());
    student->math = 2 + rand() % 4;  // Оценки от 2 до 5
    student->physics = 2 + rand() % 4;
    student->informatics = 2 + rand() % 4;
    student->next = NULL;
    return student;
}

// Функция для заполнения группы студентами
struct Groups createGroup(int groupNumber) {
    struct Groups group;
    group.Number = groupNumber;
    group.Student = NULL;

    struct Students* head = NULL;
    for (int i = 0; i < 5; i++) {
        struct Students* student = createStudent();
        student->next = head;
        head = student;
    }
    group.Student = head;
    return group;
}

void swap(struct Students* a, struct Students* b) {
    struct Students temp;
    temp = *a;
    *a = *b;
    *b = temp;
}


void Add(int groupNumber, const char* name, const char* surname, const char* patronymic, int math, int physics, int informatics) {
    if (groupNumber < 0 || groupNumber >= 5) {
        printf("Неправильный номер группы.\n");
        return;
    }

    struct Students* newStudent = (struct Students*)malloc(sizeof(struct Students));
    if (newStudent == NULL) {
        printf("Проблема с памятью.\n");
        return;
    }

    newStudent->name = strdup(name);
    newStudent->surname = strdup(surname);
    newStudent->patronymic = strdup(patronymic);
    newStudent->math = math;
    newStudent->physics = physics;
    newStudent->informatics = informatics;
    newStudent->next = NULL;

    if (Dekanat[groupNumber-1].Student == NULL) {
        Dekanat[groupNumber-1].Student = newStudent;
    }
    else {
        struct Students* currentStudent = Dekanat[groupNumber-1].Student;
        while (currentStudent->next != NULL) {
            currentStudent = currentStudent->next;
        }
        currentStudent->next = newStudent;
    }

    printf("Студент %s %s %s добавлен в группу %d\n", name, surname, patronymic, groupNumber);
}

void Delete(int groupNumber, const char* name, const char* surname, const char* patronymic) {
    if (groupNumber < 0 || groupNumber >= 5) {
        printf("Неправильный номер группы.\n");
        return;
    }

    struct Students* currentStudent = Dekanat[groupNumber-1].Student;
    struct Students* previousStudent = NULL;

    while (currentStudent != NULL) {
        if (strcmp(currentStudent->name, name) == 0 &&
            strcmp(currentStudent->surname, surname) == 0 &&
            strcmp(currentStudent->patronymic, patronymic) == 0) {
            // Найден студент для удаления
            if (previousStudent == NULL) {
                // Если удаляемый студент первый в списке
                Dekanat[groupNumber-1].Student = currentStudent->next;
            }
            else {
                previousStudent->next = currentStudent->next;
            }

            // Освобождение памяти
            free(currentStudent->name);
            free(currentStudent->surname);
            free(currentStudent->patronymic);
            free(currentStudent);

            printf("Студент  %s %s %s удалён из группы %d\n", name, surname, patronymic, groupNumber);
            return;
        }

        previousStudent = currentStudent;
        currentStudent = currentStudent->next;
    }

    printf("Студент %s %s %s не найден в группе %d\n", name, surname, patronymic, groupNumber);
}

void Deduction(){
    printf("Студенты на отчисление:\n");
    for (int i = 0; i < 5; i++) {
            struct Students* current = NULL;
            struct Students* prev = NULL;
            current = Dekanat[i].Student;
            while (current->next != NULL) {
                if (current->informatics == 2 ||current->physics == 2 || current->math == 2) {
                    printf("%s\n", current->surname);
                }
                current = current->next;
            }
    }
}

void Scholarship(){
    printf("Студенты со стипендией:\n");
    for (int i = 0; i < 5; i++) {
        struct Students* current = NULL;
        struct Students* prev = NULL;
        current = Dekanat[i].Student;
        while (current->next != NULL) {
            if (current->informatics >= 4 && current->physics >= 4 && current->math >= 4){
                printf("%s\n", current->surname);
            }
            current = current->next;
        }
    }
}

void printStudentListWithGroups() {
    for (int i = 0; i < 5; i++) {
        printf("Group %d:\n", Dekanat[i].Number);

        struct Students* current = Dekanat[i].Student;
        while (current != NULL) {
            printf("  %s %s %s %d %d %d\n", current->name, current->surname, current->patronymic, current->informatics, current->math, current->physics);
            current = current->next;
        }

        printf("\n");
    }
}



int main()
{
    char* locale = setlocale(LC_ALL, "");
    for (int i = 0; i < 5; i++) {
        Dekanat[i] = createGroup(i + 1);
    }
    printStudentListWithGroups();
    Deduction();
    Scholarship();
    Add(1, "Иван", "Иванов", "Иванович", 5, 5, 5);
    printStudentListWithGroups();
    Delete(1, "Иван", "Иванов", "Иванович");
    printStudentListWithGroups();
}