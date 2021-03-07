#include <stdio.h>
#include <stdlib.h>
#include "..//head/CKTLink.h"
//用户注册链表
static short Id = 0;
static short MAX_id = 0;
struct LoginList
{
    short id;
    Flist * address;
    struct LoginList * next;
};
static struct LoginList User_LoginList =
{
    .address = NULL,
    .next = NULL
};
//以下是接口内置函数（外界无法访问）
static void CopyList(Node * prev, Item item);
static void CKTerror_fun(void);
static void In_DeteleoneLogin(Flist * list_address);
static void operateLogin(struct LoginList * next);
static void init_Login(struct LoginList *);
//初始化链表
void InitList(Flist *list_address)
{
    *list_address = NULL;
    struct LoginList * prev = &User_LoginList;
    struct LoginList * reserve = (struct LoginList *)malloc(sizeof(struct LoginList));
    if(!reserve)
    {
        fputs("The INIT fault", stderr);
        return ;
    }
    reserve -> address = list_address;
    reserve -> id = ++Id;
    reserve -> next = (struct LoginList *)malloc(sizeof(struct LoginList));
    init_Login(reserve -> next);
    if(prev -> address == NULL)
    {
        Id--;
        prev -> address = list_address;
        prev -> id = ++Id;
        prev -> next = (struct LoginList *)malloc(sizeof(struct LoginList));
        init_Login(prev -> next);
        free(reserve -> next);
        free(reserve);
    }
    else 
    {
        while(prev -> next)
            prev = prev -> next;
        prev -> next = reserve;
    }
}
//计算链表里面有几个项
unsigned int CountListItem(const Flist * const list_address)
{
    unsigned int count = 0;
    Node * prev = *list_address;
    while(prev)
    {
        prev = prev -> next;
        count++;
    }
    return count;
}
//在链表的最后一位添加节点
enum Kbool Additem(Flist * list_address, Item item)
{
    enum Kbool Booltf = T;
    Node * prev = (Node *)malloc(sizeof(Node));
    Node * scan = *list_address;
    if(prev == NULL)
        return Booltf;
    CopyList(prev, item);
    prev -> next = NULL;
    if(scan == NULL)
        *list_address = prev;
    else
    {
        while(scan -> next != NULL)
            scan = scan -> next;
        scan -> next = prev;
    }
    return Booltf;
}
//操作链表的所有节点
void OperateAllList(const Flist * list_address, void(*pfunc)(Item item))
{
    Node * scan = *list_address;
    if(!scan)
    {
        fputs("The matter is nil", stderr);
        return ;
    }
    while(scan)
    {
        (*pfunc)(scan -> item);
        scan = scan -> next;
    }
}
//删除链表
void CreleaseL(Flist * list_address)
{
    Node * release_head = (*list_address);
    Node * release_tail = release_head -> next;
    In_DeteleoneLogin(list_address);
    free(*list_address);
    *list_address = NULL;
    while(release_tail)
    {
        release_head = release_tail;
        release_tail = release_head -> next;
        free(release_head);
        release_head = NULL;
    }
}
//删除一个节点
void DeleteItem(Flist * list_address, int(*pfunc)(Item item))
{
    Node * delete = *list_address;
    Node * previous = NULL;
    if((*pfunc)(delete -> item))
    {
        *list_address = (*list_address) -> next;
        free(delete);
        return ;
    }
    while(delete)
    {
        if((*pfunc)(delete -> item))
        {
            previous -> next = delete -> next;
            free(delete);
            delete = NULL;
            return ;
        }
        previous = delete;
        delete = delete -> next;
    }
    fputs("Detele fault", stderr);
}
//清理大师
void CKTclear(void)
{
    struct LoginList * clear = &User_LoginList;
    while(clear != NULL)
    {
        if(clear -> id > 0)
        {
            free(*(clear -> address));
            *(clear -> address) = NULL;
        }
        clear = clear -> next;
    }
    clear = &User_LoginList;
    clear = clear -> next;
    struct LoginList * clear_prev = clear;
    while(clear_prev != NULL)
    {
        free(clear_prev);
        clear = clear -> next;
        clear_prev = clear;
    }
        clear_prev = NULL;
}
//对一个链表的节点进行排序
Flist CKTlistSort(Flist * list_address, int(*rule)(Item item, Item itemaft))
{
    Node * prev, * after, * temporary, * middle;
    Flist Head = *list_address;
    enum Kbool setting;
    while(1)
    {
        setting = F;
        prev = Head;
        after = prev -> next;
        if((*rule)(prev ->item, after ->item))
        {
            setting = T;
            Head = after;
            temporary = after -> next;
            after -> next = prev;
            prev -> next = temporary;
        }
        prev = Head;
        middle = prev -> next;
        after = middle -> next;
        while(after)
        {
            if((*rule)(middle ->item, after ->item))
            {
                setting = T;
                temporary = after -> next;
                after -> next = middle;
                middle -> next = temporary;
                prev -> next = after;
                temporary = middle;
                middle = after;
                after = temporary;
            }
            prev = middle;
            middle = after;
            after = after -> next;
        }
        if(setting == F) break;
    }
    return Head;
}
//--------------------------------------------------------------------------------
//接口内置函数
//将一个项复制到一个节点
static void CopyList(Node * prev, Item item)
{
    prev -> item = item;
}
//错误清理
static void CKTerror_fun(void)
{
    fprintf(stderr,"##Error:USER_FUNCTION##");
}
//删除单个链表注册
static void In_DeteleoneLogin(Flist * list_address)
{
    enum Kbool TF = F;
    struct LoginList * temporary = &User_LoginList;
    struct LoginList * previous = temporary;
    if(*(temporary -> address) == *list_address)
    {
        operateLogin(temporary);
        User_LoginList.id = User_LoginList.next ->id;
        User_LoginList.address = User_LoginList.next -> address;
        User_LoginList.next = User_LoginList.next -> next;
        return ;
    }
    temporary = temporary -> next;
    while(temporary)
    {
        if(*(temporary -> address) == *list_address)
        {
            TF = T;
            break;
        }
        previous = temporary;
        temporary = temporary -> next;
    }
    if(TF)
    {
        operateLogin(temporary);
        previous -> next = temporary;
    }
}
//更改注册表的id
static void operateLogin(struct LoginList * next)
{
    next = next -> next;
    while(next)
    {
        next -> id = next -> id - 1;
        next = next -> next;
    }
}
static void init_Login(struct LoginList * Login)
{
    Login -> address = NULL;
    Login -> id = 0;
    Login -> next = NULL;
}