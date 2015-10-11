//
//  ConcreteObject.hpp
//  RefC
//
//  Created by Ilya Kulebyakin on 10/11/15.
//  Copyright © 2015 Ilya Kulebyakin. All rights reserved.
//

#ifndef ConcreteObject_hpp
#define ConcreteObject_hpp

#include <iostream>
#include "RootObject.hpp"

namespace RefCount {
    class ConcreteObject : public RootObject {
    public:
        RootObject *strong;
        RootObject *weak;
        void setWeak(RootObject* ptr);
        
        void setStrong(RootObject* ptr);
        
        ConcreteObject();
        ~ConcreteObject();
    };
}



#endif /* ConcreteObject_hpp */
