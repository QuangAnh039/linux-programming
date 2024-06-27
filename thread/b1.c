//Viết một chương trình thực hiện tạo 2 threads. Cả hai threads này đều dùng chung một hàm handle. Kiểm tra nếu là thread1 đang thực hiện thì in ra thông điệp bất kì để thông báo. Nếu là thread2 thì truyền vào dữ liệu kiểu struct human được khởi tạo từ trước, với các thông tin: Họ tên, năm sinh, sdt, quê quán.


#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h> 

pthread_t thread_id1, thread_id2;

typedef struct foo
{
    char name[20];
    int date;
    char phonenum[20];
    char country[20];
} human;

void *myThreadFun(void *vargp) 
{
    
    if(pthread_self() == thread_id1)
    {
        printf("Im thread 1\n");
    }
    if(pthread_self() == thread_id2)
    {
        human *tmp = (human *)vargp;
        
        printf("Im thread 2\n");
        printf("NAME: %s\n", tmp->name);
        printf("DATE: %d\n", tmp->date);
        printf("PHONE_NUMBER: %s\n", tmp->phonenum);
        printf("COUNTRY: %s\n", tmp->country);
    }
    return NULL; 
} 


int main() {
    
    human quanganh;

    strcpy(quanganh.name, "Quang Anh");
    quanganh.date = 2003;
    strcpy(quanganh.phonenum, "0898070922");
    strcpy(quanganh.country, "Ha Dong");
    pthread_create(&thread_id1, NULL, myThreadFun, NULL); 
    pthread_create(&thread_id2, NULL, myThreadFun, (void *)&quanganh); 
    pthread_join(thread_id1, NULL); 
    pthread_join(thread_id2, NULL); 

    return 0;
}