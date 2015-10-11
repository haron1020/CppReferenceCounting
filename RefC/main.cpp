//
//  main.cpp
//  RefC
//
//  Created by Ilya Kulebyakin on 10/11/15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#include <iostream>
#include "RefCount.hpp"

using namespace RefCount;


int main(int argc, const char * argv[]) {
    // All of program execution which utilizes reference counting system should be wrapped in POOL_START/POOL_END macros
    POOL_START
    
    // All constructors are required to call RootObject's constructor during thyself initializtion
    // CSO(name, initializer) stands for CreateSafeObject
    // when object, returned by this initializer is freed,
    // Pointer root1 will get a walue of nullptr
    ConcreteObject *CSO(root1, new ConcreteObject())
    
    // Puts object into autoreleasepool.
    // Reference counter is decreased by one and if it equals
    // zero, object will be deallocated when the closest
    // autorelease pool drains
    Autorelease(root1)
    
    ConcreteObject *CSO(weakLeaf, new ConcreteObject())
    
    ConcreteObject *CSO(strongLeaf, new ConcreteObject());
    
    root1->setStrong(strongLeaf);
    
    // Immediate object deallocation, if reference counter equals zero after 1 is subrtracted
    Release(strongLeaf)
    root1->setWeak(weakLeaf);
    {
        // Nested pool
        // All autoreleased objects will get into this pool
        POOL_START
    
        ConcreteObject* CSO(weak2, new ConcreteObject())
        
        strongLeaf->setWeak(weak2);
        // For example this one
        Autorelease(weak2)
        POOL_END
    }
    Release(weakLeaf)
    
    POOL_END
  
    return 0;
}
