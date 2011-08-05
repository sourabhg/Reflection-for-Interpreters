#include "Value.hpp"
#include <typeinfo>
#include <string.h>
#include <iostream>
#include <assert.h>
#include <stdlib.h>

using namespace std;



namespace cs540 {


void
IntegerValue::print() const {
 //  cout << "\n In sym " ;
   cout << this->val << "\n";    
//assert(false);
}

IntegerValue::IntegerValue(int v){
 
 
 val = v;

}
const IntegerValue *
IntegerValue::addition(const Value *in_add) const {
//    cout << "there";
    
    const IntegerValue *in_val = dynamic_cast<const IntegerValue *>(in_add);
    if(in_val == NULL)
    {
      cout << "\n Illegal Addition of different types" << "\n";
      exit(0);
    }
    int add_no = val + in_val->val;
   // cout << "\n" << add_no;
//    int add_no = val + in_val->val;
    
 //   cout << "\n addition is :" << add_no;
    const IntegerValue *ret_val = new IntegerValue(add_no);
    return ret_val;
//    assert(false);

}

const StringValue * StringValue::multiplication(const Value *) const { 
cout << "\n Invalid command";
assert(false);
}

const StringValue * StringValue::negation() const { 
cout << "\n Invalid command";
assert(false);
}

const ObjPtrValue * ObjPtrValue::multiplication(const Value *) const { 
cout << "\n Invalid command";
assert(false);
}

const ObjPtrValue * ObjPtrValue::negation() const { 
cout << "\n Invalid command";
assert(false);
}

const IntegerValue *
IntegerValue::multiplication(const Value *in_add) const {
//    cout << "there";
    
    const IntegerValue *in_val = dynamic_cast<const IntegerValue *>(in_add);
    if(in_val == NULL)
    {
      cout << "\n Illegal Addition of different types" << "\n";
      exit(0);
    }
    int add_no = val * in_val->val;
   // cout << "\n" << add_no;
//    int add_no = val + in_val->val;
    
 //   cout << "\n addition is :" << add_no;
    const IntegerValue *ret_val = new IntegerValue(add_no);
    return ret_val;
//    assert(false);

}

const IntegerValue *
IntegerValue::negation() const {
//    cout << "there";
    
    int add_no = -(val);
   // cout << "\n" << add_no;
//    int add_no = val + in_val->val;
    
 //   cout << "\n addition is :" << add_no;
    const IntegerValue *ret_val = new IntegerValue(add_no);
    return ret_val;
//    assert(false);

}

StringValue::StringValue(const std::string &sval)
{
  stval = sval;

}

void
StringValue::print() const {
    //cout << "\n In ss Here " ;
    cout << this->stval << "\n";
   // std::string nn = this->stval;
   //cout << nn << "\n";
    //assert(false);
}

const StringValue *
StringValue::addition(const Value *st_cat) const {
  const StringValue *st_val = dynamic_cast<const StringValue *>(st_cat);  
  if(st_val == NULL)
    {
      cout << "\n Illegal Addition of different types" << "\n";
      exit(0);
    }
  //char *temp = dynamic_cast<char >(stval);
  //const char *temp1 = dynamic_cast<const char >(st_val->stval);
  std :: string result = stval + st_val->stval;
  
//  cout << "\n string add : " << result << "\n";
  const StringValue *ret_val = new StringValue(result);
 // assert(false);
  return ret_val;
}


void
ObjPtrValue::print() const {
   // cout << "\n returned obj ptr " << "\n";
    assert(false);
}

const ObjPtrValue *
ObjPtrValue::addition(const Value *) const {
    assert(false);
}



}
