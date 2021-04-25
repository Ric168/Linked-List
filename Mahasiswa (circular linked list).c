#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Mahasiswa
{
    char nama[100];
    char jurusan[30];
    int nim;

    struct Mahasiswa *kanan;
} Mahasiswa;

Mahasiswa *head = NULL;
Mahasiswa *tail = NULL;

bool isEmpty()
{
    return head == NULL;
}

void createNewNode(int nim, char *nama, char *jurusan)
{
    Mahasiswa *newNode = malloc(sizeof(Mahasiswa));
    newNode->nim = nim;
    strcpy(newNode->nama, nama);
    strcpy(newNode->jurusan, jurusan);
    if (tail == NULL)
    {
        tail = newNode;
    }
    newNode->kanan = head;
    head = newNode;
    tail->kanan = head;
}

void cleanup()
{
    while (head != tail)
    {
        Mahasiswa *temp = head;
        head = head->kanan;
        free(temp);
    }
    free(head);
    head = NULL;
    tail = NULL;
}

void printLinkedList()
{
    Mahasiswa *temp = head;
    int i = 1;

    while (temp != tail)
    {
        printf("Data ke %d\n", i++);
        printf("NIM      :%d\n", temp->nim);
        printf("Nama     :%s\n", temp->nama);
        printf("Jurusan  :%s\n\n", temp->jurusan);
        temp = temp->kanan;
    }
    printf("Data ke %d\n", i++);
    printf("NIM      :%d\n", temp->nim);
    printf("Nama     :%s\n", temp->nama);
    printf("Jurusan  :%s\n\n", temp->jurusan);
}
int main()
{
    createNewNode(17492, "Matthew Evans", "Informatika");
    createNewNode(13633, "Justin Susanto", "Informatika");
    printf("Data Sebelum dihapus\n");
    printLinkedList();

    Mahasiswa *temp;
    temp = head;
    head = head->kanan;
    temp->kanan = NULL;
    free(temp);

    printf("Data Sesudah dihapus\n");
    printLinkedList();
    cleanup();
    return 0;
}
