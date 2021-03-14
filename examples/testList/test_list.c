#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include "list.h"

#define MAX_STRING_LENGTH 19

typedef struct {
    struct ListHead head;
    pthread_mutex_t mutex;
} ListParam;

typedef struct {
  char first_name[MAX_STRING_LENGTH];
  char last_name[MAX_STRING_LENGTH];
  unsigned int age;
} StudentInfoParam;

typedef struct {
    struct ListHead chain;
    StudentInfoParam studentInfo;
} ListNode;


ListNode *CreateListNode(const char *fn, const char *ln, unsigned int a) 
{
    ListNode *stu = (ListNode *)malloc(sizeof(ListNode));
    if (stu == NULL) {
        fprintf(stderr, "Failed to malloc(%d).\n", errno);
        return NULL;
    }
    
    if (strlen(fn) > (MAX_STRING_LENGTH - 1)) {
        fprintf(stderr, "First name too long.\n");
        free(stu);
        return NULL; /* First name too long. */
    }
    if (strlen(ln) > (MAX_STRING_LENGTH - 1)) {
        fprintf(stderr, "Last name too long.\n");
        free(stu);
        return NULL; /* Last name too long. */
    }

    strcpy(stu->studentInfo.first_name, fn);
    strcpy(stu->studentInfo.last_name, ln);
    stu->studentInfo.age = a;
    return stu;
}

int CreateStudents(struct ListHead *listHead)
{
    ListNode *stu = NULL;
    if ((stu = CreateListNode("Pierre", "Dupont", 16)) == NULL) {
        fprintf(stderr, "Failed to create Pierre.\n");
        return -1;
    }
    ListAddTail(&stu->chain, listHead);

    if ((stu = CreateListNode("Hugot", "Badeaux", 18)) == NULL) {
        fprintf(stderr, "Failed to create Pierre.\n");
        return -1;
    }
    ListAddTail(&stu->chain, listHead);
    
    if ((stu = CreateListNode("Celine", "Brousseau", 17)) == NULL) {
        fprintf(stderr, "Failed to create Pierre.\n");
        return -1;
    }
    ListAddTail(&stu->chain, listHead);
}


void PrintAllStudentsInfo(struct ListHead *listHead)
{
    ListNode *cur = NULL;
    
    printf("All the students in class.\n");
    list_for_each_entry(cur, listHead, chain) {
        printf("First name: %s\n", cur->studentInfo.first_name);
        printf("Last name: %s\n", cur->studentInfo.last_name);
        printf("Age: %u\n\n", cur->studentInfo.age);
    }
}

void InputInfo(void)
{
    char inputStr[20];  /*定义一个最大长度为19, 末尾是'\0'的字符数组来存储字符串*/
    printf("请输入一个字符串:");
    fgets(inputStr, sizeof(inputStr) - 1, stdin);  /*从输入流stdin即输入缓冲区中读取7个字符到字符数组str中*/
    printf("%s\n", inputStr);
}

int main(int argc, char *argv[])
{
    printf("%s\n", argv[0]);
    ListParam studentInfoList;
    pthread_mutex_init(&studentInfoList.mutex, NULL);
    InitListHead(&studentInfoList.head);    

    pthread_mutex_lock(&studentInfoList.mutex);
    CreateStudents(&studentInfoList.head);
    pthread_mutex_unlock(&studentInfoList.mutex);

    pthread_mutex_lock(&studentInfoList.mutex);
    PrintAllStudentsInfo(&studentInfoList.head);
    pthread_mutex_unlock(&studentInfoList.mutex);

    return 0;
}
