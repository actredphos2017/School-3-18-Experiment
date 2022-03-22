#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>

//list链表
#define isHead true
#define Tail -1
typedef int ElemType;
typedef int Location;
class list{
    private:
        bool ifhead = false;
        ElemType Data;
        list* next = NULL;
    public:
        //链表头初始化
        list(bool _ifhead = false){
            ifhead = _ifhead;
        }

        //函数返回判断该链表是否为头指针节点
        bool ifHead(){
            return ifhead;
        }

        //获取某个节点的数据
        ElemType read(Location _loc){
            list* p = this;
            while(p && _loc--)
                p = p->next;
            return p->Data;
        }

        //返回节点数量
        int num(){
            if(!ifhead){
                throw("Error! This is not a head point!\n");
                return -1;
            }
            list* p = this->next;
            int n = 0;
            while(p){
                p = p->next;
                n ++;
            }
            return n;
        }

        //返回单个节点的复制
        list scopy(){
            list temp;
            temp = *this;
            return temp;
        }

        //函数返回该链表的复制
        list copy(){
            if(!ifhead){
                throw("Error! This is not a head point!\n");
                exit(0);
            }
            list head(isHead), *newp = &head, *oldp = this->next;
            while(oldp){
                newp->next = new list;
                *(newp->next) = oldp->scopy();
                oldp = oldp->next;
                newp = newp->next;
            }
            return head;
        }

        //往链表中插入元素 *_loc 为下标* *_loc = Tail 表示尾插*
        void insert(ElemType _data, Location _loc){
            list* p = this;
            list *temp = new list;
            temp->Data = _data;
            if(_loc == Tail){
                while(p->next)
                    p = p->next;
                p->next = temp;
                return;
            }
            while(_loc --){
                if(p)
                    p = p->next;
                else{
                    throw("Error! Wrong Location!\n");
                    return;
                }
            }
            temp->next = p->next;
            p->next = temp;
            return;
        }

        //删除链表元素 *_loc 为下标*
        void pop(Location _loc){
            list* p = this;
            list* _p;
            while(_loc --){
                if(p->next)
                    p = p->next;
                else{
                    throw("Error!");
                    return;
                }
            }
            _p = p->next;
            p->next = p->next->next;
            delete _p;
        }

        //顺序遍历输出链表
        friend std::ostream& operator<<(std::ostream &o, const list _l);

        //删除节点元素（但不删除头节点）
        void del(){
            if(!ifhead){
                throw("Error! This is not a head point!\n");
                exit(0);
            }
            list *p[2];
            int k = 0;
            p[1] = this;
            p[0] = this->next;
            while(p[k%2]){
                p[(k+1)%2] = p[k%2]->next;
                delete p[k%2];
                k ++;
            }
            this->next = NULL;
        }

        //初始化创建一条链表，输入负数后停止
        void create(){
            if(!ifhead){
                throw("Error! This is not a head point!\n");
                return;
            }
            ElemType _data;
            list *temp, *p = this;
            while(scanf("%d",&_data) != EOF){
                if(_data < 0)
                    break;
                temp = new list;
                temp->Data = _data;
                temp->next = NULL;
                p->next = temp;
                p = p->next;
            }
        }

        //倒置链表
        void usdown(){
            if(!ifhead){
                throw("Error! This is not a head point!\n");
                exit(0);
            }
            list *newlist = new list[num()], *p = this->next;
            int k = 0;
            while(p){
                newlist[k] = *p;
                p = p->next;
                k ++;
            }
            for(int i = 0; i < k; i ++)
                newlist[i+1].next = &newlist[i];
            newlist[0].next = NULL;
            del();
            *this = newlist[k];
        }

        //重驻运算符+=实现两条链表相连
        void operator+=(const list temp){
            list tempcpy = temp;
            list cpy = tempcpy.copy();
            list* p = this;
            while(p->next)
                p = p->next;
            p->next = cpy.next;
        }

        //重驻运算符+实现两条链表相连
        const list operator+(const list temp){
            list result = copy();
            result += temp;
            return result;
        }
};

std::ostream& operator<<(std::ostream &o, const list _l){
    list l = _l, *p = l.next;
    if(!p){
        std::cout << "NULL" << std::endl;
        return o;
    }
    while(p){
        if(p == l.next)
            std::cout << p->Data;
        else
            std::cout << ", " << p->Data;
        p = p->next;
    }
    std::cout << std::endl;
    return o;
}

#endif