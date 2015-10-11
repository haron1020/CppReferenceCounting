//
//  RootObject.cpp
//  RefC
//
//  Created by Ilya Kulebyakin on 10/11/15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#include "RootObject.hpp"
#include "AutoreleasePool.hpp"

#pragma mark - Object initialization / deallocation

RootObject::RootObject() {
    _autorelease = false;
    _refCount = 1;
    _selfPtrsCount = 0;
    _selfPtrsCapacity = 1;
    _selfPtrs = new RootObject**[_selfPtrsCapacity];
}

RootObject::~RootObject() {
    for (int i = 0; i < _selfPtrsCount; ++i) {
        *(_selfPtrs[i]) = nullptr;
    }
    delete [] _selfPtrs;
};

#pragma mark - Object Reference Counting methods

void RootObject::retain() {
    _autorelease = false;
    ++_refCount;
}

void RootObject::makeSafe(RootObject** ptr) {
    if (_selfPtrsCount == _selfPtrsCapacity) {
        _selfPtrs = reallocate(_selfPtrs, _selfPtrsCapacity *= 2, _selfPtrsCount);
    }
    _selfPtrs[_selfPtrsCount++] = ptr;
}

bool RootObject::release() {
    --_refCount;
    if (_refCount <= 0 && !_autorelease) {
        return true;
    }
    return false;
}

bool RootObject::drain() {
    _autorelease = false;
    return release();
}

void RootObject::autorelease() {
    if (--_refCount == 0) {
        AutoreleasePool::addObjectToCurrentPool(this);
        _autorelease = true;
    }
}