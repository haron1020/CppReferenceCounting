//
//  RootObject.hpp
//  RefC
//
//  Created by Ilya Kulebyakin on 10/11/15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#ifndef RootObject_hpp
#define RootObject_hpp

#define Weakify(ptr) ptr->makeSafe((RootObject**)&ptr);
#define Retain(ptr) ptr->retain(); ptr->makeSafe((RootObject**)&ptr);
#define Release(ptr) if (ptr->release()) { delete ptr; };
#define Autorelease(ptr) ptr->autorelease();

#include <stdio.h>
#include "Util.hpp"

class RootObject {
    int _refCount;
    bool _autorelease;
    RootObject*** _selfPtrs;
    int _selfPtrsCount = 0;
    int _selfPtrsCapacity = 0;
    
    void freePointers();
public:
    RootObject();
    virtual ~RootObject();
    
    void retain();
    bool release();
    void autorelease();
    void makeSafe(RootObject** ptr);
    
    bool drain();
    
};

#endif /* RootObject_hpp */
