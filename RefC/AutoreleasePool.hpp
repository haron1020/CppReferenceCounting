//
//  AutoreleasePool.hpp
//  RefC
//
//  Created by Ilya Kulebyakin on 10/11/15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#ifndef AutoreleasePool_hpp
#define AutoreleasePool_hpp

#include <iostream>
#include "RootObject.hpp"

#define POOL_START { \
AutoreleasePool::startPool();

#define POOL_END AutoreleasePool::endPool(); \
                }

class AutoreleasePool {
private:
    RootObject** _objects;
    int _count;
    int _capacity;
    
    AutoreleasePool();
    ~AutoreleasePool();
    
    bool hasObject(RootObject* object);
    void addObject(RootObject* object);
    void drain();
    
    static void performPreparation();
    static void stopExecution();
    
public:
    static AutoreleasePool* startPool();
    static void endPool();
    
    static AutoreleasePool*  currentPool();
    static void addObjectToCurrentPool(RootObject* object);
    static AutoreleasePool* poolForObject(RootObject* object);
};

#endif /* AutoreleasePool_hpp */
