#include "Node.hpp"
#include <assert.h>
#include <map>
#include <string>
#include <utility>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Value.hpp"
#include "Token.hpp"
#include "Reflection.hpp"

using namespace std;



namespace cs540 {
typedef std :: map <std :: string,const Value *> Maptype;
Maptype symbol_tble;
Reflection *refl_clss = new Reflection();


namespace {
    
}



// Actual type: const IdentToken *id
// The node is just an expression.
AssignmentNode::AssignmentNode(const Token *id, const Node *e) {
    // FILL IN.
    const IdentToken *idtok = dynamic_cast<const IdentToken*>(id);
    this->Assg_t = idtok;
    this->Assg_n = e;
    
}

const Value *
AssignmentNode::execute() const {
    
    // FILL IN.
    //assert(false);
 //   cout << "\n in Ass exec";
 //   cout << "\n " << typeid((this->Assg_n)).name();
  //  cout << "\n token " << typeid((this->Assg_t)).name();
  //  cout << "\n " << typeid((this->Assg_t->ident())).name();
    std :: string key = this->Assg_t->ident();
  //  cout << key;
    const Value *t_value = dynamic_cast<const Value *>(this->Assg_n);
//    string key = this->Assg_t->ident();
    
   // cout << "\n " << typeid((t_value)).name();
    const Value *v = (this->Assg_n)->execute();
  //  cout << "\n in assgn ex " << typeid((v)).name() << "\n";
    
    symbol_tble[key] = v;
    //cout << "\n sym size :" << symbol_tble.size();
    return v;
    //return 0;
}


// Actual type: const IdentToken *t
VarNode::VarNode(const Token *t) {
    const IdentToken *idtok = dynamic_cast<const IdentToken*>(t);
    this->var_t = idtok;
  //  cout<< "\n" << idtok->code();
  //  cout << "\n var tok :" << (this->var_t)->ident();
    //this->Assg_n = e; 
    // cout << "\n varnode";
   //  cout << "\n sizeof map current " << symbol_tble.size() << "\n" ;
}

const Value *
VarNode::execute() const {
    std :: string temps = (this->var_t)->ident();   
   // cout << "in var exec " << temps;
   //  cout << "\n varnodee";
    const Value *ret_val;
    Maptype::iterator iter = symbol_tble.begin();
    iter = symbol_tble.find(temps);
    if (iter != symbol_tble.end() ) 
      {
        ret_val = iter->second;
// std::cout << "Value is: " << iter->second << '\n';
       }
       
    else 
       {
        cout << " No Such Symbol Present " << "\n";
         exit(0);
        //std::cout << "Key is not in my_map" << '\n';
       }
    
  //= sym_lookup(temps);
    //assert(false);
    //return 0;
    return ret_val;
}



// Actual type: const IntegerToken *t
IntegerNode::IntegerNode(const Token *t) {
    const IntegerToken *intok = dynamic_cast<const IntegerToken*>(t);
    //Value *ret_val = 
    this->int_tok = intok;
    //cout<< "\n" << intok->code();
    this->x = &intok->value();
    int k = this->x->value();
  //  cout << "\n int val :" << k;
    this->real_val = k;
   // cout << "\n";
   // cout << "\n int typeid " << typeid((this->int_tok)).name();
   // cout << "\n";
   
    }

const Value *
IntegerNode::execute() const {
//    cout<< "\n in ehere";
    
   // cout<< "The typid is :" << typeid((this->int_tok)).name(); 
    const IntegerValue *ret_val = new IntegerValue(this->real_val);
    return ret_val;
    //return 0;
}
 
// Actual type: const StringToken *t
StringNode::StringNode(const Token *t) {
   const StringToken *sttok = dynamic_cast<const StringToken*>(t);
   //const Token *temp_token = dynamic_cast<const Token *>(t);
   //cout << "\n token code is : " << temp_token->code();     
   this->t = sttok;
 //  cout<< "\n" << sttok->code();
   // cout<< "\n" << intok->code();
     this->st = &sttok->value();
 //   cout<< "The typid is :" << typeid((this->st)).name();
    this->real_st = this->st->value();
     
//    cout << "\n stringnode";
}

const Value *
StringNode::execute() const {
  //  cout << "\n stringnodee";
  const StringValue *ret_val = new StringValue(this->real_st);
    return ret_val;    
//assert(false);
    //return 0;
}

AdditionNode :: AdditionNode(const Node *l, const Node *r) {
    this->ll = l;
    this->rr = r;
   
}

const Value *
AdditionNode::execute() const {
   // cout << "\n addnodee";
    const Value *ret_val = ((this->ll)->execute())->addition((this->rr)->execute());
 //   (this->ll)->execute();
 //   (this->rr)->execute();
 //   cout<< "The typid is :" << typeid((ret_val)).name();
    return ret_val;
}

MultiplicationNode :: MultiplicationNode(const Node *l, const Node *r) {
    this->ll = l;
    this->rr = r;
   
}

const Value *
MultiplicationNode::execute() const {
   // cout << "\n addnodee";
    const Value *ret_val = ((this->ll)->execute())->multiplication((this->rr)->execute());
 //   (this->ll)->execute();
 //   (this->rr)->execute();
 //   cout<< "The typid is :" << typeid((ret_val)).name();
    return ret_val;
}
 
NegationNode :: NegationNode(const Node *e) {
    this->ee = e;
    
   
}

const Value *
NegationNode::execute() const {
   // cout << "\n addnodee";
    const Value *ret_val = ((this->ee)->execute())->negation();
 //   (this->ll)->execute();
 //   (this->rr)->execute();
 //   cout<< "The typid is :" << typeid((ret_val)).name();
    return ret_val;
}

// Actual type: const IdentToken *t
NewNode::NewNode(const Token *t) {
     // cout << "\n newnode";
      const IdentToken *name = dynamic_cast<const IdentToken *>(t);
      this->cname = name->ident();
      //Reflection *refl_node = new Reflection();
     // new_clss = refl_node;
}

const Value *
NewNode::execute() const {
   // refl_node->load();
    refl_clss->test();
    std :: string soname = "class_" + this->cname + ".so";
   // cout << "\n name " << soname;
    refl_clss->Load(soname);
    const ObjPtrValue *ret_val = refl_clss->New(this->cname);
    //this->new_clss->Load(soname);
    //const ObjPtrValue *ret_val = this->new_clss->New("AA");
    //cout << typeid(ret_val).name();
   // cout << "\n newnodee";
    //assert(false);
    return ret_val;
    //return 0;
}


// Node is some expression.
PrintNode::PrintNode(const Node *n) {
      //cout << "\n printnode";
      this->s = n;
     // cout << "\n" << typeid((this->s)).name();   
     
      //std :: string pchar = dynamic_cast<std :: string >(this->s); 
 }

const Value *
PrintNode::execute() const {
   // cout << "\n printnodee";
   // cout << "\n" <<typeid((this->s)).name(); 
    
    const Value *ret_val = this->s->execute();
  // 
    if(ret_val == NULL)
    {
       cout << "error";
       exit(0);
     }
    ret_val->print();
    //cout << "\n" << typeid((val)).name();   
    //(this->s)->execute();
//    assert(false);
    return ret_val;
}

// Actual types: const IdentToken *obj, const IdentToken *method
// Each node in the deque is some expression.
InvocationNode::InvocationNode(const Token *obj, const Token *method, 
 const deque<const Node *> *al) {
   //    cout << "\n invonode";
   const IdentToken *obn = dynamic_cast<const IdentToken *>(obj);
   this->ret_t = obn;
   const IdentToken *moh = dynamic_cast<const IdentToken *>(method);
   this->method = moh;
   //cout << al->size();
 //  copy(al->begin(),al->end(),inserter((this->deq),(this->deq)->begin()))
//     cout << "\n The name is:" << typeid(al->at(0)).name();
   //(al->at(0))->execute();
   this->deq = al;
   //cout << "\n" << (this->deq)->size();    
   //Reflection *refl_node = new Reflection();
   //this->go = refl_node;

//   const 

}

const Value *
InvocationNode::execute() const {
     //   cout << "\n invonodee";
    //assert(false); 
    std :: string obj_name = (this->ret_t)->ident();
    //ObjPtrValue *my_this = new ObjPtrValue();
    //cout << obj_name;
    std :: string methd = (this->method)->ident();
    //cout << methd;
    const Value *ret_val;
    Maptype::iterator iter = symbol_tble.begin();
    iter = symbol_tble.find(obj_name);
    if (iter != symbol_tble.end() ) 
      {
        ret_val = iter->second;

       }
       
    else 
       {
         cout << " No Such Symbol Present " << "\n";
         exit(0);
       
       }
    const ObjPtrValue *my_this = dynamic_cast<const ObjPtrValue *>(ret_val);
    //cout << "\n tid is : " << typeid(my_this).name();
    std::vector<const Value *> argL; 
    //cout << argL.size();
    int de_size = this->deq->size();
    
    //const Value *aval;
    int count = 0;
    for(int x = 0; x < de_size; ++x)
	{
         count ++;
      //   cout << "\n count is " << count;
         const Value *v = (this->deq->at(x))->execute();
         argL.insert(argL.begin() + x,v);
//         argL[x]->print();
	}
      const Value *d_val = refl_clss->Invoke(my_this,methd,argL);
//    for(int x = 0; x < de_size; ++x)
      // cout << argL.size();
    return d_val;
}



}
