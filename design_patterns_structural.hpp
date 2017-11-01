#ifndef DESIGN_PATTERNS_STRUCTURAL_
#define DESIGN_PATTERNS_STRUCTURAL_

#include <vector>

namespace Structural_Patterns{

  namespace Adapter{

    // The Adapter pattern allows otherwise incompatible classes to work
    // together by converting the interface of one class into an 
    // interface expected by the clients. 

    class DesiredInterface{

    public:
      virtual void make() = 0;
    };

    class LegacyInterface{
      
    public:
      LegacyInterface() { std::cout << "\tCalled legacy" << std::endl;};
    };

    // privately inherits the implementation of the legacy component

    class adapter : public DesiredInterface, private LegacyInterface{

    public:
      adapter() : LegacyInterface(){};
      void make () { std::cout << "\tAdapter do something " << std::endl;}
    };
    
  }; //end adapter

  
  namespace Bridge{
    
    //
    // Decouple an abstraction from its implementation so that the 
    // two can vary independently. This is different from
    // Adapter which makes unrelated classes work together.

    class bridge_imp_{ // de-couple

    public:
      bridge_imp_() {};
      
    protected:
      int my_data_;
    };

    class bridge{

    public:
      bridge() { new bridge_imp_(); };
      
    protected:
      bridge_imp_ * imp_;
    };

    class a_imp_ : public bridge_imp_{ // implementation hierarchy

    public:
      a_imp_() { my_data_ = 1; }// what you need here 
    };

    class a : public bridge{ // hierarchy

    public:
      a(){ imp_ = new a_imp_(); std::cout << "\tcreated a" << std::endl;};
    };

    class b_imp_ : public bridge_imp_{ // implementation hierarchy

    public:
      b_imp_() { my_data_ = 2; }; // what you need here 
    };

    class b : public bridge{ // hierarchy

    public:
      b() { imp_ = new b_imp_(); std::cout << "\tcreated b" << std::endl;};
    };

  };  // end Bridge

  namespace Composite{

    // Compose objects into tree structures to represent 
    // whole-part hierarchies. Recursive composition

    class Component{

    public:
      virtual void traverse() = 0;  // pure virtual
    };


    class Leaf : public Component{

    private:
      int value_ ; // whaever you need here

    public:
      Leaf(int val) : value_(val) {};
      void traverse() { std::cout << value_ << " "; }
    };

    class Composite : public Component{

    private:
      std::vector< Component * > children_;
      typedef std::vector< Component * >::const_iterator comp_const_it;

    public:
      void add(Component * e) { children_.push_back(e); };

      void traverse() 
      { 
	comp_const_it it = children_.begin();
	comp_const_it it_end = children_.end();
	for (; it != it_end; ++it)
	  (*it)->traverse();
      }

    };
      
  }; // end composite


  namespace Decorator{

    // Attach additional responsibilities to an object dynamically. 
    // Decorators provide a flexible alternative to subclassing for 
    // extending functionality.
    
    class A{
      
    public:
      A() { std::cout << "\tA" << std::endl; }

      virtual void make(void) { std::cout << "\t making A" << std::endl; }
    };

    //
    // the decoration is private;

    class A_and_X : public A{

    public:
      void make(void) { A::make(); make_x(); };

    private:
      void make_x() { std::cout << "\t making X" << std::endl; };
    };

  }; // end Decorator


  namespace Facade{

    // "facade" object that provides a single, simplified interface
    // to the many individual interfaces within the subsystem.

    class A{
      
    public:
      A() { std::cout << "\tInit A" << std::endl; }
      void make() { std::cout << "\tmake A" << std::endl; }
    };

    class B{

    public:
      B() { std::cout << "\tInit B" << std::endl; }   
      void make() { std::cout << "\tmake B" << std::endl; }   
    };

    class C{

    public:
      C() { std::cout << "\tInit C" << std::endl; }
      void make() { std::cout << "\tmake C" << std::endl; }
    };

    class facade{
      
    public:
      facade() { a_.make(); b_.make(); c_.make();}
    private:
      A a_;
      B b_;
      C c_;
    };
    
  }; //end facade

  
  namespace Flyweight{

    //The Flyweight pattern shares objects and reduce costs
    // in terms of memory and increase performance
    //
    // A key concept is the distinction between "intrinsic" and "extrinsic" 
    // state. Intrinsic state consists of information that is independent 
    // of the flyweight's context - information that is sharable.
    // It is stored in the flyweight. Extrinsic state cannot be shared, 
    // it depends on and varies with the lyweight's context 
    // Extrinsic state is stored or computed by the client 
    // and is passed to the flyweight when an operation is invoked. 
    //
    // Clients should not instantiate Flyweights directly, they should 
    // obtain them exclusively from a FlyweightFactory object to ensure 
    // they are shared properly. 

    class Icon { // cannot have a "huge" object for each Icon, bad performance
      
    public:
      Icon(unsigned int i): shared_name_(i) {};
      unsigned int getName(){ return shared_name_;}

    private:
      unsigned int shared_name_; // whatever you need here the shared part
    };

    class FlyweightFactory{

    public:
      static Icon * getIcon(unsigned int name) 
      { 
	std::vector<Icon *>::const_iterator it, it_end;
	it = icons_.begin();
	it_end = icons_.end();
	for (; it != it_end; ++it){
	  if ((*it)->getName() == name){
	    std::cout << "\tFlyweight -> reusing an icon with name=" 
		      << name << std::endl;
	    return *it;
	  }
	}
	icons_.push_back(new Icon(name));
	std::cout << "\tCreated a new icon with name=" << name << std::endl;
	return icons_.back();
      }; // an example: get an Icon allocated

    private:
      static std::vector<Icon *>icons_; 
    };
    
    std::vector<Icon *> FlyweightFactory::icons_; // force allocation
  }; // end Flyweight

  
  namespace Proxy{

    // The Proxy provides a surrogate to provide access to an object. 
    // RL Example: A check or bank draft is a proxy for funds in an account.

    // Decorator and Proxy have different purposes but similar structures.
    // Both describe how to provide a level of indirection to another object, 
    // and the implementations keep a reference to the object to which they
    // forward requests (delegation)

    class ImageProxy{
      
    private:
      unsigned int name_;

    public:
      ImageProxy(unsigned int name) : name_(name) 
      { std::cout << "\tCreating image name=" << name_ << std::endl; };

      ~ImageProxy() 
      { std::cout << "\tDelete image name=" << name_ << std::endl; };
      
      void draw() 
      { std::cout << "\tDraw image name=" << name_ << std::endl; };
    };

    class Image{

    private:
      ImageProxy * img_proxy_;
      static unsigned int name_;
      
    public:
      Image() : img_proxy_(0) {};
      ~Image() { delete img_proxy_; };

      void draw ()
      { 
	if (!img_proxy_)
	  img_proxy_ = new ImageProxy(name_++);

	img_proxy_->draw();
      }
    };
    
    unsigned int Image::name_ = 0;
    
  }; // end Proxy

};
#endif
