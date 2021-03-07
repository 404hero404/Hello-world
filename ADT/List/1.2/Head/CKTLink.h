//2021.3.4建立文档
/*链表ADT 1.1*/
/*陈柯廷*/
#ifndef CKTLINK
#define CKTLINK
#define NAME_LEN 45
enum Kbool {F,T};//kbool类型，T正确，F错误
//链表内容的一般形式，可更改
struct item
{
    unsigned int id;
    char name[NAME_LEN];
};
typedef struct item Item;
//链表的链接结构
typedef struct node
{
    Item item;
    struct node * next;
} Node;
typedef Node * Flist;
    //以下是处理函数
    /*
        函数作用：初始化链表（作者备注：定义好一个链表以后，第一步必须初始化）
        无返回值
        list_address:链表地址
    */
    void InitList(Flist * list_address);
    /*
        函数作用：计算链表有几个项
        返回链表中有几个项
        list_address:链表地址
    */
    unsigned int CountListItem(const Flist * const list_address);
    /*
        函数作用：在链表的末尾添加项
        返回是否添加成功
        list_address:链表地址
        item:添加项的内容
    */
    enum Kbool Additem(Flist * list_address, Item item);
    /*
        函数作用：对链表的每个项进行操作（具体如何操作由用户定义的函数实现）
        无返回值
        list_address:链表地址
        *pfunc:一个用户自定义函数，由用户操控项目
    */
    void OperateAllList(const Flist * list_address, void(*pfunc)(Item item));
    /*
        函数作用：删除其中的项
        无返回值
        list_address:链表地址
        id:需要删除的学生学号
    */
    void DeleteItem(Flist * list_address, int(*pfunc)(Item item));
    /*
        函数作用：释放链表占用的空间（当这个链表已经别无他用时，请使用这个函数）
        无返回值
        list_address:链表地址
    */
    void CreleaseL(Flist * list_address);
    /*
        函数作用：结尾清理，当程序结束时，请必定使用该函数
        无参数
    */
    void CKTclear(void);
    /*
        函数作用：对节点进行排序（排序方法由用户提供的函数决定）
        无返回值
        list_address: 链表地址
        *rule:用户提供的方法
    */

    Flist CKTlistSort(Flist * list_address, int(*rule)(Item item, Item itemaft));
#endif