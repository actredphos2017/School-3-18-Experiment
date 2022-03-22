#include <iostream>
#include "include/link.h"

#if 1

int main(){
    Link a(isHead);
    for(ElemType i = 0; i < 12; i ++)
        a.insert(i,0);
    std::cout << a;
    a.usdown();
    std::cout << a;
    return 0;
}

#else

#include "include/hash.h"

int main(){
    Location loc;
    ElemType data;
    Link a(isHead);
    char* cmd;
    cmd = new char[10];
    while(1){
        std::cin >> cmd;
        switch(hash_(cmd)){
            case hash_compile_time("help"):
                std::cout << "insert"   << std::endl
                          << "pop"      << std::endl
                          << "usdown"   << std::endl
                          << "del"      << std::endl
                          << "lout"     << std::endl
                          << "create"   << std::endl
                          << "num"      << std::endl
                          << "read"     << std::endl
                          << "exit"     << std::endl;
                break;
            case hash_compile_time("insert"):
                std::cin >> loc >> data;
                a.insert(data,loc);
                break;
            case hash_compile_time("pop"):
                std::cin >> loc;
                a.pop(loc);
                break;
            case hash_compile_time("usdown"):
                a.usdown();
                break;
            case hash_compile_time("del"):
                a.del();
                break;
            case hash_compile_time("print"):
                std::cout << a;
                break;
            case hash_compile_time("create"):
                a.create();
                break;
            case hash_compile_time("num"):
                std::cout << a.num() << std::endl;
                break;
            case hash_compile_time("read"):
                std::cin >> loc;
                a.read(loc);
                break;
            case hash_compile_time("exit"):
                return 0;
            default:
                std::cout << "Unknown command! Enter \"help\" to Link the command you can use!" << std::endl;
                break;
        }
    }
    return 0;
}

#endif