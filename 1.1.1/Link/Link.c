#include <stdio.h>
#include <stdlib.h>
#include "..//Head/CKTLink.h"
static short Id = 0;    //用户注册链表的个数
//注册表的结构
struct LoginList
{
    short id;   //链表序号
    Flist * address;    //链表的地址
    struct LoginList * next;    //下一张链表
};
//初始化一张注册表
static struct LoginList * User_LoginList;
//以下是接口内置函数（外界无法访问）
static void CopyList(Node * prev, Item item);//把一个项复制到一个节点
static int CKTerror_fun(Flist);//函数错误提示
static void In_DeteleoneLogin(Flist * list_address);//删除注册表
static void operateLogin(struct LoginList * next);//对注册表中当前链表后面进行序号减一
static void init_Login(struct LoginList *);//初始化注册表
static int Request_LoginMemory(struct LoginList * add);//判断注册表内存是否获取成功
static void CKTclear(void); //程序扫尾
//初始化链表
void InitList(Flist *list_address)
{
    //链表初始化为NULL
    *list_address = NULL;
    struct LoginList * prev = User_LoginList;//获取第一张注册表的地址
    struct LoginList * reserve = (struct LoginList *)malloc(sizeof(struct LoginList));
    //判断内存是否获取成功
    if(!Request_LoginMemory(reserve)) return ;
    reserve -> address = list_address;//将链表地址注册到注册表
    reserve -> id = ++Id;//给链表添加序号
    reserve -> next = (struct LoginList *)malloc(sizeof(struct LoginList));
    //判断内存是否获取成功
    if(!Request_LoginMemory(reserve)) return ;
    init_Login(reserve -> next);
    if(prev -> address == NULL)//检查一下这个链表是不是第一个链表
    {
        atexit(CKTclear);
        prev = reserve;
    }
    else 
    {
        prev = prev -> next;
        while(prev -> address)
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
//操作链表的节点
void OperateAllList(const Flist * list_address, void(*pfunc)(Item item))
{
    Node * scan = *list_address;
    if(!CKTerror_fun(scan)) return ;
    while(scan)//遍历所有节点
    {
        (*pfunc)(scan -> item);//执行用户的函数
        scan = scan -> next;
    }
}
//删除链表
void CreleaseL(Flist * list_address)
{
    Node * release_head = (*list_address);
    Node * release_tail = release_head -> next;
    //删除注册表
    In_DeteleoneLogin(list_address);
    Id--;
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
    if((*pfunc)(delete -> item))    //如果第一个节点就需要删除
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
        if((*rule)(prev ->item, after ->item))//第一个项（特殊情况）
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
static int CKTerror_fun(Flist address)
{
    if(address == NULL)
    {
        fprintf(stderr,"##Error:USER_FUNCTION_Argument##");
        return 0;
    }
    return 1;
}
//删除链表的注册表
static void In_DeteleoneLogin(Flist * list_address)
{
    enum Kbool TF = F;
    struct LoginList * temporary = User_LoginList;//需要删除的注册表
    struct LoginList * previous = temporary;    //需要删除的注册表的前驱
    if(*(User_LoginList -> address) == *list_address)   //如果第一个注册表就是需要删除
    {
        operateLogin(User_LoginList);
        User_LoginList = User_LoginList -> next;
        free(temporary);
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
        previous -> next = temporary -> next;
        free(temporary);
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
//把下一张注册表初始化
static void init_Login(struct LoginList * Login)
{
    Login -> address = NULL;
    Login -> id = 0;
    Login -> next = NULL;
}
//请求注册表内存是否成功
static int Request_LoginMemory(struct LoginList * add)
{
    if(add == NULL)
    {
        fputs("The INIT fault", stderr);
        return 0;
    }
    return 1;
}
//清空链表清空注册表
static void CKTclear(void)
{
    struct LoginList * clear = User_LoginList;
    while(clear)
    {
        CreleaseL(clear -> address);
        clear = clear -> next;
    }
}