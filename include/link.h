#ifndef __LINK_H__
#define __LINK_H__

#include <iostream>

//list链表
#define isHead true
#define Tail -1
typedef int ElemType;
typedef int Location;
class Link{
    private:
        bool ifhead = false;
        ElemType Data;
        Link* next = NULL;
    public:
        //链表头初始化
        Link(bool _ifhead = false){
            ifhead = _ifhead;
        }

        //函数返回判断该链表是否为头指针节点
        bool ifHead(){
            return ifhead;
        }

        //获取某个节点的数据
        ElemType read(Location _loc){
            Link* p = this;
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
            Link* p = this->next;
            int n = 0;
            while(p){
                p = p->next;
                n ++;
            }
            return n;
        }

        //返回单个节点的复制
        Link scopy(){
            Link temp;
            temp = *this;
            return temp;
        }

        //函数返回该链表的复制
        Link copy(){
            if(!ifhead){
                throw("Error! This is not a head point!\n");
                exit(0);
            }
            Link head(isHead), *newp = &head, *oldp = this->next;
            while(oldp){
                newp->next = new Link;
                *(newp->next) = oldp->scopy();
                oldp = oldp->next;
                newp = newp->next;
            }
            return head;
        }

        //往链表中插入元素 *_loc 为下标* *_loc = Tail 表示尾插*
        void insert(ElemType _data, Location _loc){
            Link* p = this;
            Link *temp = new Link;
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
            Link* p = this;
            Link* _p;
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
        friend std::ostream& operator<<(std::ostream &o, const Link _l);

        //删除节点元素（但不删除头节点）
        void del(){
            if(!ifhead){
                throw("Error! This is not a head point!\n");
                exit(0);
            }
            Link *p[2];
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
            Link *temp, *p = this;
            while(scanf("%d",&_data) != EOF){
                if(_data < 0)
                    break;
                temp = new Link;
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
            Link *newlist = new Link[num()], *p = this->next;
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
        void operator+=(const Link temp){
            Link tempcpy = temp;
            Link cpy = tempcpy.copy();
            Link* p = this;
            while(p->next)
                p = p->next;
            p->next = cpy.next;
        }

        //重驻运算符+实现两条链表相连
        const Link operator+(const Link temp){
            Link result = copy();
            result += temp;
            return result;
        }
};

std::ostream& operator<<(std::ostream &o, const Link _l){
    Link l = _l, *p = l.next;
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