//
//  Container.hpp
//  RefC
//
//  Created by Andrey Nazarov on 11.10.15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#ifndef Container_hpp
#define Container_hpp
#include "RootObject.hpp"

template <typename T>
class Container: public RefCount::RootObject {
    void* var;
public:
    void(*deallocator)(T* res);
    Container(T res);
    Container();
};

template <typename T>
Container<T>::Container(T res){
    var = new char [sizeof(T)];
    memcpy(var, &res, sizeof(T));
    std::cout<< *reinterpret_cast<T*>(var)<<std::endl;
}
template <typename T>
Container<T>::Container(){
    // std::cout<<sizeof(T);
    var = new char [sizeof(T)];
    std::cout<<var;
}

#endif /* Container_hpp */
