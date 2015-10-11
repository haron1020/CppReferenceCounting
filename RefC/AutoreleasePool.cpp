//
//  AutoreleasePool.cpp
//  RefC
//
//  Created by Ilya Kulebyakin on 10/11/15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#include "AutoreleasePool.hpp"
#include "Util.hpp"

#pragma mark - Global variables

int _poolsCount;
int _poolsCapacity;
AutoreleasePool** _pools;

#pragma mark - AutoreleasePool instance methods

AutoreleasePool::AutoreleasePool() {
    _count = 0;
    _capacity = 2;
    _objects = new RootObject*[_capacity];
}

AutoreleasePool::~AutoreleasePool() {
    delete [] _objects;
}

void AutoreleasePool::addObject(RootObject* object) {
    if (_count == _capacity) {
        _objects = reallocate(_objects, _capacity *= 2, _count);
    }
    _objects[_count++] = object;
}

void AutoreleasePool::drain() {
    for (int i = 0; i < _count; ++i) {
        if (_objects[i]->drain()) {
            delete _objects[i];
        }
    }
}

bool AutoreleasePool::hasObject(RootObject* object) {
    for (int i = 0; i < _count; ++i) {
        if (_objects[i] == object) {
            return true;
        }
    }
    return false;
}


#pragma mark - AutoreleasePool class methods

void AutoreleasePool::performPreparation() {
    _poolsCapacity = 2;
    _poolsCount = 0;
    _pools = new AutoreleasePool*[_poolsCapacity];
}

AutoreleasePool* AutoreleasePool::startPool() {
    static bool onceTokenUnused = true;
    if (onceTokenUnused) {
        performPreparation();
        onceTokenUnused = false;
    }
    if (_poolsCount == _poolsCapacity) {
        _pools = reallocate(_pools, _poolsCapacity *= 2, _poolsCount);
    }
    _pools[_poolsCount++] = new AutoreleasePool();
    return _pools[_poolsCapacity - 1];
}

AutoreleasePool* AutoreleasePool::currentPool() {
    if (_poolsCount == 0) {
        return nullptr;
    }
    return _pools[_poolsCount - 1];
}

void AutoreleasePool::endPool() {
    currentPool()->drain();
    delete currentPool();
    if (--_poolsCount == 0) {
        stopExecution();
    }
}

void AutoreleasePool::stopExecution() {
    for (int i = 0; i < _poolsCount; ++i) {
        _pools[i]->drain();
        delete _pools[i];
    }
    delete [] _pools;
}

AutoreleasePool* AutoreleasePool::poolForObject(RootObject* object) {
    for (int i = 0; i < _poolsCount; ++i) {
        if (_pools[i]->hasObject(object)) {
            return _pools[i];
        }
    }
    return nullptr;
}

void AutoreleasePool::addObjectToCurrentPool(RootObject* object) {
    if (poolForObject(object)) {
        return;
    }
    AutoreleasePool* pool = currentPool();
    pool->addObject(object);
}
