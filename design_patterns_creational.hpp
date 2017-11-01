#ifndef DESIGN_PATTERNS_CREATIONAL_
#define DESIGN_PATTERNS_CREATIONAL_

#include <iostream>
#include <vector> 

namespace Creational_Patterns{

  namespace Abstract_Factory{

    // The Factory pattern suggests defining a creation services interface
    // in a Factory base class, and implementing each "platform" in a 
    // separate Factory derived class.
    
    class Widget{
      
    public:
      virtual void draw() = 0; // make it pure virtual
    
    };
    
    class OSX_Button : public Widget{
      
    public:
      void draw() { std::cout << "\tOSX buttom" << std::endl; }
    };
    
    class Windows_Button : public Widget{
      
    public:
      void draw() { std::cout << "\tWindows buttom" << std::endl; }
    };
  };  // end Abstract Factory

  namespace Builder{

    // Separate the construction of a complex object from its
    // representation so that the same construction process can 
    // create different representations.

   
    class Build{     // base class

    public:
      virtual void configure() = 0;
      
      // here you can add some methods to see the internal state

    protected:
      int configuration_1_ ;  // here you put all the confs variable
      int configuration_2_ ;  // here you put all the confs variable
      //...
      int configuration_n_ ;  // here you put all the confs variable


    };
    
    class SimpleBuilder : public Build { // a derived class
      
    public:
      SimpleBuilder() { std::cout << "\tSimple Builder" << std::endl;};
      void configure() 
      { /// 
      };
    };

    class AdvancedBuilder : public Build { // a derived class
      
    public:
      AdvancedBuilder() { std::cout << "\tAdvanced Builder" << std::endl;};
      void configure() 
      { /// 
      };
    };


    // the class that use multiple builders

    class ClientClass{
      
    public:
      
      ClientClass(Build * builder) : builder_(builder){};

    private:
      Build * builder_;    // set the specific builder
    };

  }; // end Builder


  namespace Factory_Method{

    // Define an interface for creating an object, 
    // but let subclasses decide which class to instantiate. 
    // Factory Method lets a class defer instantiation to subclasses.
    //
    // Factory Method can return the same instance multiple times, 
    // or can return a subclass rather than an object of that exact type.
    
    // Abstract Factory classes are often implemented with Factory Methods, 
    // but they can be implemented using Prototype.
    
    // Factory Method is similar to Abstract Factory but without
    // the emphasis on families.

    // In general all the derived class maybe used together

    class Base{

    public:
      virtual void what_to_do() = 0;

    };
    
    class A : public Base{
    public:
      A() { std::cout << "\tClass A"<< std::endl;}
      void what_to_do() { };

    };

    class B : public Base{
    public:
      B() { std::cout << "\tClass B"<< std::endl;}
      void what_to_do() { };

    };
  }; // end Factory Method

  
  namespace Object_Pool{

    // Object pools are used to manage the object caching. 
    // A client with access to a Object pool can avoid creating 
    // a new Objects by simply asking the pool for one that has 
    // already been instantiated instead.

    // As an example think about database connections

    static const int num_objects = 3; // just an example, should be not fixed

    class Object_to_share{
      
    public:
      Object_to_share(){ std::cout << "\tAn object to share" <<std::endl;};

    };

    class Pool{

    public:
      Object_to_share * getObject(void)
      { std::cout<< "\tGetting object" <<std::endl; 
	return &(objpool_[0]);    // whatever policy you need to adopt
      }

    private:
      
      Object_to_share objpool_[num_objects]; // could allocate dynamically
    };

  }; // end ObjectPool


  namespace Prototype{
    
    // Specify the kinds of objects to create using a prototypical instance,
    // and create new objects by copying this prototype.
    
    // Declare an abstract base class that specifies a pure virtual "clone"
    // method, and, maintains a dictionary of all "cloneable" concrete 
    // derived classes. Any class that needs a "polymorphic constructor" 
    // capability: derives itself from the abstract base class, 
    // registers its prototypical instance, and implements the clone() 
    // operation.

    enum clone_type { type_a = 1, type_b = 2 };// different types
    static const int num_protos_ = 2;          // this can be dynamic
    
    //
    // base proto
    //
    class Proto{

    public:
      // return the appropriate clone
      static Proto * findAClone(clone_type t);

      // inspect its type
      virtual clone_type returnType(void) = 0;

    protected:

      virtual Proto* clone() = 0; // derived class must implement clone()

      static void add_a_proto(Proto * proto)
      { prototypes_[next_slot_++] = proto;
	// std::cout << "\tRegistering prototype " << proto->returnType()
	// << " next slot is " << next_slot_ << std::endl;
      };
	
    private:
      static Proto *prototypes_[num_protos_];  // each proto is stored here 
      static unsigned int next_slot_;          // better to make dynamic
    };

    //
    // for finding a clone
    //
    Proto * Proto::prototypes_[];
    unsigned int Proto::next_slot_;
    Proto * Proto::findAClone(clone_type t)
    {
      for (unsigned int i = 0; i < next_slot_; i++)
	if (prototypes_[i]->returnType() == t)
	  return prototypes_[i]->clone();	      
      
      return 0;
    }
        
    class A : public Proto{ // a derived prototype

    public:
      clone_type returnType(void) { return type_a; }
      Proto * clone() { return new A(1);}   // cloning here
      A(int dummy){};

    private:
      static A a_register_it_;  // register this subclass
      A()                       // call this costructor
      { add_a_proto(this);};
    };    
    A A::a_register_it_;  
    // force the default constructor to be called and register the clone
    

  }; // end Protype


  namespace Singleton{

    // Ensure a class has only one instance, 
    // and provide a global point of access to it.
    
    // The singleton pattern must be carefully constructed 
    // in multi-threaded applications.
    // The classic solution to this problem is to use mutual exclusion
    // on the class that indicates that the object is being instantiated.



    class Single{

    public:
      static Single * getInstance(void) {
	if (instance_ == NULL){
	  instance_ = new Single();
	}
	return instance_;
      };
      
    protected:
      Single(){ std::cout << "\tSingle" << std::endl;};// cannot be invoked
      
    private:
      static Single * instance_;  // a single instance
    };

    Single *Single::instance_;  // force instanciation

  }; // end Singleton


};

#endif  


