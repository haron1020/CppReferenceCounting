//
//  Util.hpp
//  RefC
//
//  Created by Ilya Kulebyakin on 10/11/15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#import <iostream>

template <typename T>
T* reallocate(T* what, int newSize, int oldSize) {
    if (newSize <= oldSize) {
        return what;
    }
    T* tmp = new T[newSize];
    std::copy(what, what + oldSize, tmp);
    delete [] what;
    return tmp;
}
