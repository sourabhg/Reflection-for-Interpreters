#ifndef CS540_VALUE_HPP
#define CS540_VALUE_HPP



#include <typeinfo>
#include <string>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

namespace cs540 {

class Value {
    public:
        virtual ~Value() {}
        const std::type_info &type() const { return typeid(*this); }
        virtual void print() const = 0;
        virtual const Value *addition(const Value *) const = 0;
        virtual const Value *multiplication(const Value *) const = 0;
        virtual const Value *negation() const = 0;
    private:
};

class IntegerValue : public Value {
    public:
        IntegerValue(int v);
        int value() const {return val;}
        virtual void print() const;
        virtual const IntegerValue *addition(const Value *) const;
        virtual const IntegerValue *multiplication(const Value *) const;
        virtual const IntegerValue *negation() const;
        int val;
    private:
        
};

class StringValue : public Value {
    public:
        StringValue(const std::string &);
        const std::string &value() const {return stval;}
        virtual void print() const;
        // Note the co-variance.
        virtual const StringValue *addition(const Value *) const;
        virtual const StringValue *multiplication(const Value *) const ;
        virtual const StringValue *negation() const ;
        std :: string stval;
    private:
        
};

class ObjPtrValue : public Value {
    public:
        virtual void print() const ;
        // Note the co-variance.  This function should cause
        // an error, since it doesn't have any meaning.
        virtual const ObjPtrValue *addition(const Value *) const;
        virtual const ObjPtrValue *multiplication(const Value *) const;
        virtual const ObjPtrValue *negation() const ;
    private:
         ObjPtrValue *myobj;
};


}



#endif
