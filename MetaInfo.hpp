#ifndef CS540_META_INFO_HPP
#define CS540_META_INFO_HPP



#include <string>
#include <vector>
#include "Value.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

namespace cs540 {



class MetaInfo {
    public:
        virtual ~MetaInfo() {}
        virtual ObjPtrValue *create() = 0;
        virtual Value *icall(const ObjPtrValue *, const std::string &method_name, const std::vector<const Value *> &args) = 0;
        virtual std::string className() const = 0 ;
};

class MetaInfoRegisterer {
    public:
        MetaInfoRegisterer(const MetaInfo *);
};



}



#endif
