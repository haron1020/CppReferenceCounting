//
//  ConcreteObject.cpp
//  RefC
//
//  Created by Ilya Kulebyakin on 10/11/15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#import "ConcreteObject.hpp"

namespace RefCount {
    ConcreteObject::ConcreteObject() : RootObject() {
        strong = nullptr;
        weak = nullptr;
    }
    
    void ConcreteObject::setWeak(RootObject* ptr) {
        weak = ptr;
        rfc_Safify(weak);
    }
    
    void ConcreteObject::setStrong(RootObject* ptr) {
        strong = ptr;
        rfc_Retain(strong);
    }
    
    ConcreteObject::~ConcreteObject() {
        if (strong) {
            rfc_Release(strong);
        }
    }
}

