//
//  main.cpp
//  RefC
//
//  Created by Ilya Kulebyakin on 10/11/15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#include <iostream>
#include "RootObject.hpp"
#include "AutoreleasePool.hpp"
#include "ConcreteObject.hpp"



int main(int argc, const char * argv[]) {
    // All of program execution which utilizes reference counting system should be wrapped in POOL_START/POOL_END macros
    POOL_START
    
    // All constructors are required to call RootObject's constructor during thyself initializtion
    ConcreteObject *root1 = new ConcreteObject();
    
    // Temporary macro to make pointer safe. If at any moment during execution object, that root1 points to will be deallocated, root1 pointer will get a value of nullptr
    Safify(root1)
    // Puts object into autoreleasepool.
    // Reference counter is decreased by one and if it equals
    // zero, object will be deallocated when the closest
    // autorelease pool drains
    Autorelease(root1)
    
    ConcreteObject *weakLeaf = new ConcreteObject();
    Safify(weakLeaf)
    
    ConcreteObject *strongLeaf = new ConcreteObject();
    Safify(strongLeaf)
    root1->setStrong(strongLeaf);
    
    // Immediate object deallocation, if reference counter equals zero after 1 is subrtracted
    Release(strongLeaf)
    root1->setWeak(weakLeaf);
    {
        // Nested pool
        // All autoreleased objects will get into this pool
        POOL_START
    
        ConcreteObject* weak2 = new ConcreteObject();
        Safify(weak2)
        strongLeaf->setWeak(weak2);
        // For example this one
        Autorelease(weak2)
        POOL_END
    }
    Release(weakLeaf)
    
    POOL_END
  
    return 0;
}
