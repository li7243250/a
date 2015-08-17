//
//  Singleton.h
//  MyTouchTouch
//
//  Created by mac mini on 15/5/12.
//
//

#ifndef __MyTouchTouch__Singleton__
#define __MyTouchTouch__Singleton__

#include "Common.h"

template <typename T>
class Singleton {
    
public:
    void setInstance(T *ins){
        instance = ins;
    };
    
    static T* getInstance(){
        return instance;
    }


    static T* instance;
};

template <typename T>
 T* Singleton<T>::instance = nullptr;

#endif /* defined(__MyTouchTouch__Singleton__) */
