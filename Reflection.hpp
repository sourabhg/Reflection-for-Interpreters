#ifndef REFLECTION_HPP
#define REFLECTION_HPP



#include <string>
#include <vector>
#include "MetaInfo.hpp"


namespace cs540 {



class ObjPtrValue;

class Value;

class mfactory {
   public:
      virtual ObjPtrValue *create(const std :: string &tname) const = 0;
     
};

class Reflection {
    public:
        void test();
        Reflection ();
        void Load(const std::string &);
        const ObjPtrValue *New(const std::string &type_name);
        const Value *Invoke(const ObjPtrValue *, const std::string &method_name, const std::vector<const Value *> &args);
        void *handle;
        MetaInfo *t_meta;
        // Other things can go here of course.
        // ...
};



}



#endif
