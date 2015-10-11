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
   
    POOL_START
    
    ConcreteObject *root1 = new ConcreteObject();
    Weakify(root1)
    Autorelease(root1)
    
    ConcreteObject *weakLeaf = new ConcreteObject();
    Weakify(weakLeaf)
    
    ConcreteObject *strongLeaf = new ConcreteObject();
    Weakify(strongLeaf)
    root1->setStrong(strongLeaf);
    Release(strongLeaf)
    root1->setWeak(weakLeaf);
    {
        POOL_START
    
        ConcreteObject* weak2 = new ConcreteObject();
        Weakify(weak2)
        strongLeaf->setWeak(weak2);
        Autorelease(weak2)
        POOL_END
    }
    Release(weakLeaf)
    
    POOL_END
  
    return 0;
}
