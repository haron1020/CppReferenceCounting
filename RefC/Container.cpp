//
//  Container.cpp
//  RefC
//
//  Created by Andrey Nazarov on 12.10.15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#include "Container.hpp"

template <typename T>
RefCount::Container<T>::Container(T* res, deallocator<T> deallocatorFunc){
    resource = res;
    this->deallocatorFunc = deallocatorFunc;
}

template <typename T>
RefCount::Container<T>::~Container<T>(){
    if(deallocatorFunc == nullptr)
        delete resource;
    else deallocatorFunc();
}
