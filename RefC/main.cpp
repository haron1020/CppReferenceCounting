//
//  main.cpp
//  RefC
//
//  Created by Ilya Kulebyakin on 10/11/15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#import <iostream>
#import "RefCount.hpp"
#include "Container.hpp"

using namespace RefCount;


int main(int argc, const char * argv[]) {
    // All of program execution which utilizes reference counting system should be wrapped in POOL_START/POOL_END macros
    rfc_AUTORELEASE_POOL_START
    
    // All constructors are required to call RootObject's constructor during thyself initializtion
    // CSO(name, initializer) stands for CreateSafeObject
    // when object, returned by this initializer is freed,
    // Pointer root1 will get a walue of nullptr
    ConcreteObject *rfc_CSO(root1, new ConcreteObject())
    
    // Puts object into autoreleasepool.
    // Reference counter is decreased by one and if it equals
    // zero, object will be deallocated when the closest
    // autorelease pool drains
    rfc_Autorelease(root1)
    
    ConcreteObject *rfc_CSO(weakLeaf, new ConcreteObject())
    
    ConcreteObject *rfc_CSO(strongLeaf, new ConcreteObject());
    
    root1->setStrong(strongLeaf);
    
    // Immediate object deallocation, if reference counter equals zero after 1 is subrtracted
    rfc_Release(strongLeaf)
    root1->setWeak(weakLeaf);
    {
        // Nested pool
        // All autoreleased objects will get into this pool
        rfc_AUTORELEASE_POOL_START
    
        ConcreteObject* rfc_CSO(weak2, new ConcreteObject())
        
        strongLeaf->setWeak(weak2);
        // For example this one
        rfc_Autorelease(weak2)
        rfc_AUTORELEASE_POOL_DRAIN
    }
    rfc_Release(weakLeaf)
    
    rfc_AUTORELEASE_POOL_DRAIN
    
    
    
        char * b = new char [3];
        b[0] = '1';
        b[1] = '2';
        b[2] = '\0';
        auto a = Container<typeof b>(b);
        auto d = Container<double>(5.3);
        auto c = Container<int>(3);
  
    return 0;
}
