#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#pragma warning (disable :4996)

int count = 0;

typedef struct student {
    int number;
    char name[10];
    float total;
}stu;

typedef struct NODE {
    stu data;
    struct NODE* link;
}node;

node* insert(node* head, stu data) {
    node* p = (node*)malloc(sizeof(node)); //동적 메모리 할당을 이용해서 새로운 노드 p를 생성
    p->data.number = data.number;
    strcpy(p->data.name, data.name);
    p->data.total = data.total;
    p->link = head; //헤드 포인터의 값을 복사함
    head = p; //헤드 포인터 변경
    return head;
}

void total_change(node* head) {

    stu temp;

    for (node* p = head; p->link != NULL; p = p->link)
    {
        for (node* q = p->link; q != NULL; q = q->link) //p->link가 null이 아니어야함
        {
            if (p->data.total > q->data.total)
            {
                temp.total = p->data.total;
                p->data.total = q->data.total;
                q->data.total = temp.total;

                temp.number = p->data.number;
                p->data.number = q->data.number;
                q->data.number = temp.number;

                strcpy(temp.name, p->data.name);
                strcpy(p->data.name, q->data.name);
                strcpy(q->data.name, temp.name);
            }
        }
    }

    for (node* p = head; p != NULL; p = p->link)
    {
        printf("학번: %d, 이름: %s, 총점: %f\n", p->data.number, p->data.name, p->data.total);
    }

}

void number_change(node* head) {

    stu temp;

    for (node* p = head; p->link != NULL; p = p->link)
    {
        for (node* q = p->link; q != NULL; q = q->link)
        {
            if (p->data.number > q->data.number)
            {
                temp.total = p->data.total;
                p->data.total = q->data.total;
                q->data.total = temp.total;

                temp.number = p->data.number;
                p->data.number = q->data.number;
                q->data.number = temp.number;

                strcpy(temp.name, p->data.name);
                strcpy(p->data.name, q->data.name);
                strcpy(q->data.name, temp.name);
            }
        }
    }

    for (node* p = head; p != NULL; p = p->link) {
        printf("학번: %d, 이름: %s, 총점: %f\n", p->data.number, p->data.name, p->data.total);
    }
}

void name_change(node* head) {

    stu temp;

    for (node* p = head; p->link != NULL; p = p->link)
    {
        for (node* q = p->link; q != NULL; q = q->link)
        {
            if (strcmp(p->data.name, q->data.name) > 0)
            {
                temp.total = p->data.total;
                p->data.total = q->data.total;
                q->data.total = temp.total;

                temp.number = p->data.number;
                p->data.number = q->data.number;
                q->data.number = temp.number;

                strcpy(temp.name, p->data.name);
                strcpy(p->data.name, q->data.name);
                strcpy(q->data.name, temp.name);
            }
        }
    }

    for (node* p = head; p != NULL; p = p->link) {
        printf("학번: %d, 이름: %s, 총점: %f\n", p->data.number, p->data.name, p->data.total);
    }

}

int main() {
    FILE* fp = NULL;
    char c_tem[10];
    int n = 0;

    stu test;
    stu* s;

    node* head = NULL;
    stu temp; // 임시 데이터 저장 공간 실제 사용x

    if ((fp = fopen("data.txt", "r")) == NULL)
        printf("파일 열기 실패\n");

    while (!feof(fp)) {
        fscanf(fp, "%d %s %f", &temp.number, c_tem, &temp.total);
        count++;
    }

    rewind(fp); //파일포인터를 맨 앞으로 옮김
    s = (stu*)malloc(sizeof(stu) * count); //현재 데이터 개수만큼 동적할당

    while (!feof(fp)) {
        fscanf(fp, "%d %s %f", &test.number, c_tem, &test.total);
        strcpy(test.name, c_tem);
        head = insert(head, test);
        printf("%d %s %f\n", test.number, test.name, test.total);
    }
    printf("\n");


    printf("\n");
    printf("총점 낮은 순으로 정렬(오름차순)\n");
    total_change(head);

    printf("\n");
    printf("학번 낮은 순으로 정렬(오름차순)\n");
    number_change(head);

    printf("\n");
    printf("이름 빠른 순으로 정렬(오름차순)\n");
    name_change(head);

    free(s); // 메모리 누수 방지(동적할당)
    fclose(fp);
    return 0;
}