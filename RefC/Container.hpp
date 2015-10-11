//
//  Container.hpp
//  RefC
//
//  Created by Andrey Nazarov on 11.10.15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#import "RootObject.hpp"

template <typename T>
class Container: public RefCount::RootObject {
    T* var;
protected:
    void(*deallocator)(T* res);
public:
    Container(T* res);
    Container(T* res, void(*deallocator)());
};

template <typename T>
Container<T>::Container(T* res){
    var = res;
}
template <typename T>
Container<T>::Container(T* res, void(*deallocator)()){
    var = nullptr;
}