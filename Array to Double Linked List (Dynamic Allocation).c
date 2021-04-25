#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Student
{
    char name[50], NIM[20], grade[2], major[20];
    int task, midTerm, finalTerm;
    float score;

    struct Student *kanan, *kiri;

    //float gpa;
} Student;

Student *head;

void createNewNode1(char *name, char *NIM, char *major, int task, int midTerm, int finalTerm, float score, char *grade)
{
    Student *newNode = (struct Student *)malloc(sizeof(struct Student));
    strcpy(newNode->NIM, NIM);
    strcpy(newNode->name, name);
    strcpy(newNode->major, major);
    newNode->task = task;
    newNode->midTerm = midTerm;
    newNode->finalTerm = finalTerm;
    newNode->score = score;
    strcpy(newNode->grade, grade);

    newNode->kiri = NULL;
    newNode->kanan = head;
    if (head != NULL)
    {
        head->kiri = newNode; //calonHead
    }
    head = newNode;
}

void cariDanHapus(char *NIM)
{
    Student *temp = head;
    while (temp != NULL)
    {
        if (strcmp(NIM, temp->NIM) == 0)
        {
            if (temp->kanan != NULL)
            {
                temp->kanan->kiri = temp->kiri;
            }

            if (temp->kiri != NULL)
            {
                temp->kiri->kanan = temp->kanan;
            }

            if (head == temp)
            {
                head = temp->kanan;
            }
            temp->kiri = NULL;
            temp->kanan = NULL;
            free(temp);
            temp = NULL;
            printf("NIM ketemu dan berhasil dihapus\n\n");
            return;
        }
        temp = temp->kanan;
    }
    printf("NIM tidak ketemu\n\n");
}

void printLinkedList()
{
    Student *temp = head;
    while (temp != NULL)
    {
        printf("Linked List awal");

        temp = temp->kanan;
    }
}

int hitungJumlahRecord()
{
    int ret = 0;
    Student *temp = head;
    while (temp != NULL)
    {
        ++ret;
        temp = temp->kanan;
    }
    return ret;
}

void hapusSemua()
{
    while (head != NULL)
    {
        Student *temp = head;
        head = head->kanan;
        temp->kiri = NULL;
        temp->kanan = NULL;
        free(temp);
        temp = NULL;
    }
    head = NULL;
}

void masukkan()
{
    struct Student student;

    printf("Insert student information\n");
    printf("Nama   :  ");
    scanf("%s", &student.name);
    printf("NIM    : ");
    scanf("%s", &student.NIM);
    printf("Jurusan: ");
    scanf("%s", &student.major);

    // FILE *fp = fopen("dataMahasiswa.txt", "a");
    // while (!feof(fp))
    // {
    //     fprintf(fp, "%s#%s#%s\t\n", student.NIM, student.name, student.major);
    // }
    // fclose(fp);

    int task, midTerm, finalTerm;
    printf("Insert Student Score: \n- - - - - - - - - -\t\n");
    printf("Task        :  ");
    scanf("%d", &task);
    fflush(stdin);
    printf("Mid Term    : ");
    scanf("%d", &midTerm);
    fflush(stdin);
    printf("Final Term  : ");
    scanf("%d", &finalTerm);
    fflush(stdin);

    float score = ("%f + %f + %f", 0.3 * task + 0.3 * midTerm + 0.4 * finalTerm);
    printf("Final Score : %.2f\n", score);
    char *grade;
    if (score >= 95 && score <= 100)
    {
        grade = "A+";
    }
    else if (score >= 85 && score <= 94.99)
    {
        grade = "A";
    }
    else if (score >= 80 && score <= 84.99)
    {
        grade = "A-";
    }
    else if (score >= 75 && score <= 79.99)
    {
        grade = "B+";
    }
    else if (score >= 70 && score <= 74.99)
    {
        grade = "B";
    }
    else if (score >= 65 && score <= 69.99)
    {
        grade = "C";
    }
    else if (score >= 60 && score <= 64.99)
    {
        grade = "C-";
    }
    else if (score >= 50 && score <= 59.99)
    {
        grade = "D";
    }
    else
    {
        grade = "F";
    }
    printf("Grade       : %s\n", grade);

    // FILE *fn = fopen("nilaiMahasiswa.txt", "a");
    // fprintf(fn, "%s#%d#%d#%d#%.*f#%s\r\n", student.NIM, task, midTerm, finalTerm, 1, score, grade);
    // fclose(fn);

    createNewNode1(student.name, student.NIM, student.major, task, midTerm, finalTerm, score, grade);
}

int main(int current_index)
{
    int i;
    int menu;

    char name[50], NIM[20], grade[2], major[20];
    int task, midTerm, finalTerm;
    float score;

    FILE *fp = fopen("dataMahasiswa.txt", "r");
    FILE *fn = fopen("nilaiMahasiswa.txt", "r");
    while (!feof(fp) && !feof(fn))
    {
        fscanf(fp, "%[^#]#%[^#]#%[^\n]\n", &NIM, &name, &major);
        fscanf(fn, "%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%s", &NIM, &task, &midTerm, &finalTerm, &score, &grade);
        createNewNode1(name, NIM, major, task, midTerm, finalTerm, score, grade);
    }
    fclose(fp);
    fclose(fn);

    do
    {
        printf("Welcome to simple student database (%d)\n", hitungJumlahRecord());

        printf("1. Input New Student\n2. Show All Students\n3. Show All Scores\n4. Hapus NIM\n0. Exit\nChoose : ");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
        {
            masukkan();
            printf("Inserting data\n\nNew students added\nPress any key to continue\n");
            break;
        }
        case 2:
        {
            Student *temp = head;
            int j = 1;
            while (temp != NULL)
            {
                printf("|%-4d|%-25s |%-15s | %-10s\t|\t\n", j++, temp->name, temp->major, temp->NIM);
                temp = temp->kanan;
            }
            // hapusSemua();
            break;
        }

        case 3:
        {
            printf("\t\t\tList Of Student Information\n");
            printf("-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  \n");
            printf("|No. |\t\tNIM\t|TASK\t|Mid Term| Final Term| Total |Grade\t|\n");
            printf("-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --  \n");

            int j = 1;
            Student *temp = head;
            while (temp != NULL)
            {
                printf("|%d   |%-10s\t|%d\t | %d\t |%d\t\t |%f\t |%s\t|\n", j++, temp->NIM, temp->task, temp->midTerm, temp->finalTerm, temp->score, temp->grade);
                temp = temp->kanan;
            }
            break;
        }

        case 4:
        {
            printf("\nMasukkan NIM : ");
            scanf("%s", &NIM);
            cariDanHapus(NIM);
        }
        }
    } while (menu != 0);

    hapusSemua();

    return 0;
}
