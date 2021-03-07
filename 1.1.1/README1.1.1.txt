链表操作ADT接口
Version 1.1.1    作者：陈柯廷;
开发环境：{
    Macos 10.15.7;
    VScode 1.54.1;
    Apple clang version 12.0.0 (clang-1200.0.32.29);
    C11;
    -----
    paralles desktop虚拟机
    Windows10 1903 （18362.30）
    gcc 8.1.0
    C17
    编译通过
}
头文件:CKTLink.c    源文件:Link.c
//有些函数返回该类型
Kbool {F,T};
//可以自定义链表中单个节点的项目，便于处理不同结构-->请更改CKTLink.h中item的结构
链表类型名：Flist         //Flist list;
    /*
        初始化链表
        list_address:链表地址
    */
    void InitList(Flist * list_address);
该操作函数，十分重要，声明好一个链表后，请一定要使用该函数进行初始化
################################################################################################
    /*
        函数作用：计算链表有几个项
        返回链表中有几个项
        list_address:链表地址
    */
    unsigned int CountListItem(const Flist * const list_address);
################################################################################################
    /*
        函数作用：在链表的末尾添加项
        返回是否添加成功
        list_address:链表地址
        item:添加项的内容
    */
    enum Kbool Additem(Flist * list_address, Item item);
################################################################################################
    /*
        函数作用：对链表的节点进行操作（具体如何操作由用户定义的函数实现）
        list_address:链表地址
        *pfunc:一个用户自定义函数，由用户操控项目
    */
    void OperateAllList(const Flist * list_address, void(*pfunc)(Item item));
pfunc写法举例：
//输出item中的id和name
void printlist(Item item)
{
    printf("id:%u\n", item.id);
    printf("name:%s\n", item.name);
}
/*更多玩法期待你的探索*/
################################################################################################
    /*
        函数作用：删除其中的项
        list_address:链表地址
        id:需要删除的学生学号
    */
    void DeleteItem(Flist * list_address, int(*pfunc)(Item item));
pfunc写法举例：
//删除id = 1的项
int deleteitem(Item item)
{
    if(item.id == 1)
        return 1;
    return 0;
}
/*更多玩法期待你的探索*/
################################################################################################
    /*
        函数作用：释放链表占用的空间（当这个链表已经别无他用时，请使用这个函数）
        list_address:链表地址
    */
    void CreleaseL(Flist * list_address);
如果用将同一个变量名来记录其他链表，释放完链表后，请再次使用初始化函数
################################################################################################
    /*
        函数作用：对节点进行排序（排序方法由用户提供的函数决定）
        list_address: 链表地址
        *rule:用户提供的方法
    */
    函数使用冒泡排序法
    Flist CKTlistSort(Flist * list_address, int(*rule)(Item item, Item itemaft));
    备注rule函数返回值是真时，则交换。
rule举例：
将名字排序。
int sortname(Item prev, Item after)
{
    if(strcmp(prev.name, after.name) > 0)
        return 1;
    else
        return 0;
}/*更多玩法期待你的探索*/
################################################################################################
