//
//  UserDataManager.h
//  TouchFish
//
//  Created by mac mini on 15/8/13.
//
//

#ifndef __TouchFish__UserDataManager__
#define __TouchFish__UserDataManager__

#include "Common.h"

enum class Lock {
    UnLock,
    CanLock,
    Locked
};

class UserDataManager:public Singleton<UserDataManager> {
    bool init();
    
    int weight;
    int mp;
    
    
public:
    
};

#endif /* defined(__TouchFish__UserDataManager__) */
