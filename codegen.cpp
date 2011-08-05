#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <map>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include "Emitter.hpp"

using namespace std;



/*
 * These are the type codes:
 *   _135: void
 *   _126: int
 *   _139: const char *
 */

/*
 * Simple example to parse a file given as a single argument, walk
 * down the DOM, and emit a file named after the input file name.
 */

void print_element_names(xmlNode *, Emitter &, Emitter &);
void print_arguments(xmlNode *, Emitter &, Emitter &);
string base_name(const std::string &fn);
int cc = -1,flag = 0;
int val_flag =0;
char vf;
char vl;
//char *meth;
char meth[50];

int
main(int argc, char *argv[]) { 
    memset(meth,0,sizeof(meth));
    if (argc != 2) {
        fprintf(stderr, "Usage: ./cg_xml input_xml_file\n");
        exit(1);
    }

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    /*
     * This initializes the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    /*parse the file and get the DOM */
    doc = xmlReadFile(argv[1], NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", argv[1]);
    }

    // Probably will not actually need anything in the .hpp file.
    string bn = base_name(argv[1]) + "_meta";

    ofstream hpp_file((bn + ".hpp").c_str());
    assert(hpp_file.good());
    Emitter hpp_emitter(&hpp_file);
    hpp_emitter.emitLine("/*  This file is generated.  DO NOT MODIFY DIRECTLY!  */");
    hpp_emitter.emitLine("");

    ofstream cpp_file((bn + ".cpp").c_str());
    assert(cpp_file.good());
    Emitter cpp_emitter(&cpp_file);
    cpp_emitter.emitLine("/*  This file is generated.  DO NOT MODIFY DIRECTLY!  */");
    cpp_emitter.emitLine("");

    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);
    print_element_names(root_element, hpp_emitter, cpp_emitter);
    cpp_emitter.emitLine(0,"Value *ret_value = NULL;");
    cpp_emitter.emitLine(0,"return ret_value;");
    cpp_emitter.emitLine(-1,"}");
    /*free the document */
    xmlFreeDoc(doc);

    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();

    return 0;
}

void
print_element_names(xmlNode *a_node, Emitter &hpp_em, Emitter &cpp_em) {

    xmlNode *cur_node = NULL;
    xmlAttr * aptr;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
		
            // Look for elements named "Class".
            if (!strcmp((const char *) cur_node->name, "Class")) {
                printf("Class Name: ");
                // The name of the class is in the attribute named
                // "name", so look through the attributes.
                aptr = cur_node->properties;
                while (aptr) {			    
                    if (!strcmp((const char *) aptr->name, "name")) {
                        // The value of the attribute is here.
                        const string class_name((const char *) aptr->children->content);
                        printf("%s\n", class_name.c_str());
                        // Make $$ in the emitted text get replaced
                        // with the class name, for convenience.
                        cpp_em.setReplacement(class_name + "_meta");
                        cpp_em.emitLine("#include \"MetaInfo.hpp\"");
                        cpp_em.emitLine("#include <assert.h>");
                        cpp_em.emitLine("#include <vector>");
                        cpp_em.emitLine("#include <iostream>");
                        cpp_em.emitLine("#include <string>");
                        cpp_em.emitLine("#include \"" +  class_name + ".hpp\"  ");
                        cpp_em.emitLine("#include \"Reflection.cpp\"");
                        cpp_em.emitLine("#include \"Value.hpp\"");
                        cpp_em.emitLine("");
                        cpp_em.emitLine("using namespace std;");
                        cpp_em.emitLine("using namespace cs540;");
                        cpp_em.emitLine("");
                        cpp_em.emitLine("class $$ : public MetaInfo {");
                        cpp_em.emitLine(1, "public:");
                        cpp_em.emitLine(1, "virtual ObjPtrValue *create();");
                        cpp_em.emitLine(0, "virtual Value *icall(const ObjPtrValue *obj, const string &,const vector<const Value *> &);");
                        cpp_em.emitLine(0, "virtual string className() const;");
                        cpp_em.emitLine(-2, "};");
                        cpp_em.emitLine("");
                        cpp_em.emitLine("extern \"C\" ObjPtrValue * $$ :: create()  {");
                        cpp_em.emitLine(1,"return new ObjPtrValue_tmpl<" + class_name + ">(new "+ class_name + ");");
                        cpp_em.emitLine(-1, "}");
                        cpp_em.emitLine("string");
                        cpp_em.emitLine("$$::className() const {");
                        cpp_em.increment_indent_level();
                     /*   for (int i = 0; i < 10; i++) {
                            // Shows use of formatted emit.
                            cpp_em.emitLineF("cout << %d << endl;", i);
                        }*/
                        cpp_em.emitLine("return \"$$\";");
                        cpp_em.emitLine(-1, "}");
                        cpp_em.emitLine("");
                        cpp_em.emitLine("namespace {");
                        cpp_em.emitLine(1, "$$ m;");
                        cpp_em.emitLine(-1, "}");
                        cpp_em.emitLine("");
                        cpp_em.emitLine("MetaInfo *mi = &m;");
         cpp_em.emitLine("extern \"C\" Value * $$ :: icall(const ObjPtrValue *obj, const string &method_name, const vector<const Value *> &args) {");	
         //        cpp_em.emitLine( "}");
           cpp_em.emitLine(1,"const ObjPtrValue_tmpl<" + class_name + "> *opv = dynamic_cast<const ObjPtrValue_tmpl<" + class_name +"> *>(obj);");
           cpp_em.emitLine( "if(opv == NULL){ cout << \"Error\"; assert(false);} ");
           cpp_em.emitLine( class_name + " *ap = opv->m_obj;"); 
                    }
                    	   
                    aptr = aptr->next;
                   
                }
                
                printf("Fields\n");			  
            }
           
            // Look for elements named Method.
            if (!strcmp((const char *) cur_node->name, "Method")) {
                printf("Method Name: ");
                //const char* meth;
                 cc = -1; 
                 flag = 0;
                 //val_flag = 0;                   
      //cpp_em.emitLine( "}");
                // The return type is in an attribute.
                aptr = cur_node->properties;
                while (aptr) {
                     if (!strcmp((const char *) aptr->name,"name")) {
                        sprintf(meth,"%s",aptr->children->content);
                       // cpp_em.emitLineF("/* Method: %s */", aptr->children->content);
                       cout << "\n type is : " <<typeid(aptr->children->content).name();
                      // strcpy(meth,(const char *)aptr->children->content);
                       cpp_em.emitLineF("if(method_name == \"%s\"){",aptr->children->content);
                    //   cout << meth;   	
                    }
                   
                    if (!strcmp((const char *) aptr->name, "returns")) {
                        printf("Returns: ");
                        printf("%s\n",aptr->children->content);
                        if(strcmp((const char *)aptr->children->content, "_137")==0)
                         {
                           //val_flag = 1;
                           vf = 's';
                           cpp_em.emitLine("StringValue *ret_value;");  
                           cpp_em.emitLine("std :: string ret;");                    
                         }
                        if(strcmp((const char *)aptr->children->content, "_141")==0)
                         {
                           //val_flag = 2;
                           vf = 'i';
                           cpp_em.emitLine("IntegerValue *ret_value;");
                           cpp_em.emitLine("int ret;");
                         }
                        if(strcmp((const char *)aptr->children->content, "_146")==0)
                         {
                           vl = 'v'; 
                           cpp_em.emitLine("StringValue *ret_value = new StringValue(\"void\");");  
                           //cpp_em.emitLine("IntegerValue *ret_value;");
                           //cpp_em.emitLine("int ret;");
                         }
                    }
                    // The name of the method is also an attribute.
                    
                    aptr = aptr->next;
                    
                }
               // cout << meth;
                print_arguments(cur_node->children, hpp_em, cpp_em);
             //  cpp_em.emitLineF("%s;",meth);		  
              //  cpp_em.emitLineF( "%d;",cc);		  
                cout << vl;
                if(vl != 'v')
                {
                 //cout << "\n true \n";
                 cpp_em.emitLineF("ret = ap->%s(",meth);
                 for(int k = 0; k <= cc ; k++)
                 {
                  cpp_em.emitLineF("arg_%d",k);
                  if(k != (cc)){ cpp_em.emitLine(","); }
                  
                 }		  
                cpp_em.emitLine(");");
                if(vf == 's')
                  {
                    cpp_em.emitLine("const StringValue *f_ret = new StringValue(ret);");
                    cpp_em.emitLine("return f_ret;");
                  }
                else
                if(vf == 'i') 
                  {
                     cpp_em.emitLine("IntegerValue *f_ret = new IntegerValue(ret);");
                    cpp_em.emitLine("return f_ret;");
                  }
                //cpp_em.emitLine("");
                }
               else {
                cpp_em.emitLineF("ap->%s(",meth);
                 for(int k = 0; k <= cc ; k++)
                 {
                  cpp_em.emitLineF("arg_%d",k);
                  if(k != (cc)){ cpp_em.emitLine(","); }
                  
                 }
                cpp_em.emitLine(");");
               }
                
               cc++;
                 
               // cpp_em.emitLine( "return ret_value;");		  
                cpp_em.emitLine( "}");		  
            }			  
		
          
        }
       		
        print_element_names(cur_node->children, hpp_em, cpp_em);
         
    }
  	
}

void
print_arguments(xmlNode *a_node, Emitter &hpp_em, Emitter &cpp_em) {

    xmlNode *cur_node = NULL;
    xmlAttr * aptr;
    
    char buffer[30];
    memset(buffer,0,sizeof(buffer));
   
    printf("Method Arguments\n");

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {

            // Method Arguments
            if (!strcmp((const char *) cur_node->name,"Argument")) {
                // The name and type are both attributes.
                aptr = cur_node->properties;
                
                
                while (aptr) {
                    
                    if (!strcmp((const char *) aptr->name,"name")) {
                        printf("Name: ");
                        printf("%s\n",aptr->children->content);
                        //cpp_em.emitLineF("%s;",aptr->children->content);
                    }
                    if (!strcmp((const char *) aptr->name,"type")) {
                        printf("Type: ");
                        printf("%s\n",aptr->children->content);
                        cc++;
                        if(strcmp((const char *)aptr->children->content, "_137")==0)
                         {
                          
                         // cout << "\n the count is : " <<cc;
                          //itoa(cc,buffer,10);
                          cpp_em.emitLineF("const StringValue *arg_val_%d = dynamic_cast<const StringValue *>(args.at(%d));",cc,cc);
                          cpp_em.emitLineF("std :: string sarg_%d = arg_val_%d->value();",cc,cc);
                          cpp_em.emitLineF("const char *arg_%d = sarg_%d.c_str();;",cc,cc);
                          //cpp_em.emitLine("StringValue *ret_value = dynamic_cast<StringValue *>(args.at(0));");                    
                         }
                        if(strcmp((const char *)aptr->children->content, "_141")==0)
                         {
                           cpp_em.emitLineF("const IntegerValue *arg_val_%d = dynamic_cast<const IntegerValue *>(args.at(%d));",cc,cc);
                           cpp_em.emitLineF("int arg_%d = arg_val_%d->value();",cc,cc);
                         }
                        
 
                    }
                    aptr = aptr->next;

                }
            }
        }
    }
}

string
base_name(const std::string &fn) {
    string base = fn;
    // Search for . to find the file extension.
    string::size_type pos = base.find('.');
    if (pos == string::npos) {
        fprintf(stderr, "File name %s not in right form.\n", base.c_str());
        exit(1);
    }
    // Truncate the file extension.
    base.erase(pos);
    cerr << "base: " << base << endl;
    return base;
}
