//
//  Container.hpp
//  RefC
//
//  Created by Andrey Nazarov on 11.10.15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#import "RootObject.hpp"



namespace RefCount {
    template <typename T>
    using deallocator = void(*)(T* res);
    
    template <typename T>
    class Container: public RefCount::RootObject {
        T* resource;
    protected:
        deallocator<T> deallocatorFunc;
    public:
        Container(T* res, deallocator<T> deallocatorFunc = nullptr);
        ~Container();
    };
}

//template <typename T>
//using deallocator = void(*)(T* res);
