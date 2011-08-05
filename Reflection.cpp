#include "Reflection.hpp"
#include "MetaInfo.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include <map>
#include "Value.hpp"

using namespace std;



class AA {
    public:
        int f() { return 1234; }
};

namespace cs540 {

typedef std :: map <std :: string,MetaInfo * > Mapty;
Mapty refl_tble;
typedef std :: map <const ObjPtrValue *,std :: string> Mapty1;
Mapty1 refl_tble1;

template <typename T>
class ObjPtrValue_tmpl : public ObjPtrValue {
    public:
        ObjPtrValue_tmpl(T *t) : m_obj(t) {}
        virtual void print() const;
    //public:
        T *const m_obj;
};

template <typename T>
void
ObjPtrValue_tmpl<T>::print() const {
    cout << m_obj << endl;
}


Reflection :: Reflection () {  
  //cout << "\n call gng \n " ; 

}

void Reflection:: test()
{
  //cout << "\n test";
}
void
Reflection::Load(const string &so_file) {
//   cout << "\n in here"; 
   this->handle = dlopen(("./" + so_file).c_str(), RTLD_LAZY|RTLD_GLOBAL);
    if (this->handle == 0) {
        cerr << dlerror() << endl;
        abort();
    }
   else
    {
  //    cout << "\n Successful \n " ;
    }
}

const ObjPtrValue *
Reflection::New(const string &type_name) {
    char name[40];
   // cout << "Instantiation of type " << type_name << " requested." << endl;
   // cout << "CHANGE THIS: " << " currently hard-code to type AA." << endl;
    void *hh = dlsym(this->handle,"mi");
     if (hh == 0) {
        cerr << dlerror() << endl;
        abort();
    }
   else
    {
    //  cout << "\n Successful \n " ;
    }
    
    MetaInfo *minfo = *(MetaInfo **)hh;
    t_meta = minfo;
    const ObjPtrValue *ret_val = minfo->create();
    refl_tble[type_name] = minfo;
    refl_tble1[ret_val] = type_name;
    //cout << type_name;
    //cout << "\n typename :" << typeid().name() ;
 //   ObjPtrValue_tmpl<type_name> *opv = dynamic_cast<ObjPtrValue_tmpl<type_name> *>(ret_val);
    //const ObjPtrValue_tmpl<type_name> *obj = const new ObjPtrValue_tmpl<type_name>(new type_name);
 //   sprintf(name,"%s",typeid(opv->m_obj).name());
    //cout << "\n typename :" << typeid(obj->m_obj).name() ;
    //char temp[30];
   // cout << "\n name is : " << name << "\n";
    return ret_val;
    //return new ObjPtrValue_tmpl<AA>(new AA);
}

const Value *
Reflection::Invoke(const ObjPtrValue *obj, const string &method_name,
 const vector<const Value *> &args) {
   // printf("Invoke:\n"); 
    std :: string tempd;
    //Metainfo *ts;
    //const ObjPtrValue *check_val;
    Mapty1::iterator iter1 = refl_tble1.begin();
    iter1 = refl_tble1.find(obj);
    if (iter1 != refl_tble1.end() ) 
      {
        tempd = iter1->second;
      //  cout << " Found ";
// std::cout << "Value is: " << iter->second << '\n';
        Mapty::iterator iter2 = refl_tble.begin();
        iter2 = refl_tble.find(tempd);
        if (iter2 != refl_tble.end() ) 
        {
        this->t_meta = iter2->second;
       // cout << " Found ";
// std::cout << "Value is: " << iter->second << '\n';
         //cout << method_name << endl;
         for (size_t i = 0; i < args.size(); i++) {
           args[i]->print();
       }
//    cout << typeid(this->t_meta).name() << endl; 
       Value *v = (this->t_meta)->icall(obj,method_name,args);
       return v;
        }
       
      else 
       {
        cout << " No Such Symbol Present " << "\n";
         exit(0);
        //std::cout << "Key is not in my_map" << '\n';
       }     
       }
       
    else 
       {
        cout << " No Such Symbol Present " << "\n";
         exit(0);
        //std::cout << "Key is not in my_map" << '\n';
       }
    // cout <<"bb"<< typeid(obj).name() << endl;
    
    //return 0;
}


}
