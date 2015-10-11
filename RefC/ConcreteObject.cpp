//
//  ConcreteObject.cpp
//  RefC
//
//  Created by Ilya Kulebyakin on 10/11/15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#include "ConcreteObject.hpp"

ConcreteObject::ConcreteObject() : RootObject() {
    strong = nullptr;
    weak = nullptr;
}

void ConcreteObject::setWeak(RootObject* ptr) {
    weak = ptr;
    Weakify(weak);
}

void ConcreteObject::setStrong(RootObject* ptr) {
    strong = ptr;
    Retain(strong);
}

ConcreteObject::~ConcreteObject() {
    if (strong) {
        Release(strong);
    }
}