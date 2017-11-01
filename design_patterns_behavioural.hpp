#ifndef DESIGN_PATTERNS_BEHAVIOURAL_
#define DESIGN_PATTERNS_BEHAVIOURAL_

#include<list>

namespace Behavioural_Patterns{

  namespace Chain_Of_Responsability{
    
    // Decoupling the sender of a request and its receiver
    // It gives more than one object a chance to handle the request

    class Base
    {
    public :
      Base(unsigned int name) :  name_(name), next_(0) {};
      void add(Base* n)  // add to the chain
      { 
	if (next_)
	  n->setPointer(next_);
	next_ = n;   
      }
      void setPointer(Base * p) { next_ = p; }
      
      virtual void handle(unsigned int who){
	
	if (who == name_)
	  std::cout << "\t" << name_ << " is the one" << std::endl;
	if (next_)
	  next_->handle(who);
      }
      
    protected:
      unsigned int name_;

    private:
      Base * next_;
    };

    class H1 : public Base{

    public:
      H1(unsigned int name) : Base(name) {  };

      void handle(unsigned int who){
	std::cout << "\tHandler H1" << std::endl;
	Base::handle(who);
      }
    };

    class H2 : public Base{

    public:
      H2(unsigned int name) : Base(name) {  };

      void handle(unsigned int who){
	std::cout << "\tHandler H2" << std::endl;
	Base::handle(who);
      }
    };
  }; // end Chain_Of_Responsability

  namespace Command{

    // Command decouples the object that invokes the operation 
    // from the one that knows how to perform it.

    
    class client{

    public:
      void client_function(int param){ // client method

	std::cout << "\tcalled client function with param " 
		  << param << std::endl;
      };
    };
    

    class command{  // abstract class, just defining execute

    public:
      virtual void execute(int what) = 0;
    };
    
    class a_specific_command : 
      public command{ // de-coupled by the specific command
      
    private:
      // the particular function
      typedef void(client::*action)(int); 
      client * receiver_;      
      action action_;

    public:
      a_specific_command (client * r, action a) : 
	receiver_(r), action_(a){};

      // invoke the action callback registered
      void execute(int what)
      { (receiver_->*action_)(what); };  
    };

  }; // end command

  
  namespace Iterator{

    // An aggregate object such as a list should give you 
    // a way to access its elements without exposing its 
    // internal structure. 

    class stack
    {
    private:
      int items_[100];  // should be dynamic
      int sp_;          // current item           

    public:
      friend class iterator; // friend it to access iterator
      stack() { sp_ = -1; }
      
      void push(int in) { items_[++sp_] = in; }
      int pop() { return items_[sp_--]; }
      bool isEmpty() { return (sp_ == -1); }
    };

    class iterator{

    private:
      const stack &stk_;  // access the structure
      int index_;

    public:
      iterator(const stack &s) : stk_(s), index_(0)
      {}      // initialize the iterator
      
      void operator++() 
      { ++index_; }

      int operator()()  // get the end of structure
      { return index_ != stk_.sp_ +1 ;}

      int operator *()
      { return stk_.items_[index_]; }
    }; 

    bool operator == (const stack &s1, 
		      const stack &s2)
    {
      iterator it1(s1), it2(s2);

      for (; it1(); ++it1, ++it2)
	if (*it1 != *it2)
	  return false;
      
      return true;
    }
  }; // end Iterator


  namespace Mediator{

    // Define an object that encapsulates how a set of objects interact. 
    // promotes loose coupling

    // Quite general design pattern
    // for example a list is mediating between node objects

    class node {

    private:
      int v_;

    public:
      node (int v) : v_(v){};
      int getValue() { return v_; }
    };

    class list { // mediating nodes

    private:
      std::vector<node *> values_;
      typedef std::vector<node *>::const_iterator const_it;
  
    public:
      void add(node *n){ values_.push_back(n);}
      void traverse() 
      { const_it it1 = values_.begin();
	const_it it2 = values_.end();
	for (; it1 != it2; it1++)
	  std::cout << " " << (*it1)->getValue();
	std::cout << std::endl;
      }
    };

  }; // end mediator

  namespace Memento{

    // The client requests a Memento from the source object 
    // when it needs to checkpoint the source object's state
    // If the client subsequently needs to "rollback" the 
    // source object's state, it hands the Memento back to 
    // the source object for reinstatement.

    class memento{ // memento

    public:
      memento(int val) : value_(val) {};
      
    private:
      friend class client;
      int value_;
    };
    
    class client{ // client
      
    public:
      client(int value) : value_(value) {};
      void increment() { ++value_; } // change of state;
      int get_value() { return value_; }

      memento * create_memento() { return new memento(value_) ; }
      void restore_from_memento(memento * m) { value_ = m->value_; }
      
    private:
      int value_;

    };

  }; // end memento

  namespace Observer{

    // when one object changes state, 
    // all its dependents are notified and updated automatically.
    
    class observer{

    public:
      virtual void update(int value) = 0;
    };

    class a_observer : public observer{

    public:
      void update(int value) 
      { std::cout << "\ta seeing " << value << std::endl; }
    };

    class b_observer : public observer{

    public:
      void update(int value) 
      { std::cout << "\tb seeing " << value << std::endl; }
    };

    class subject{

    private:
      int value_;
      std::vector<observer *>  observers_;
      typedef std::vector<observer *>::const_iterator const_it;

    public:
      void set_value(int value) { value_=value; notify(); }

      // attach the observers
      void attach(observer * o) { observers_.push_back(o); }
      void notify()
      { 
	const_it it = observers_.begin(), it_end = observers_.end();
	for (; it != it_end; ++it)
	  (*it)->update(value_);
      }
    };
  }; // end observer

  namespace State {
    
    // Allow an object to alter its behavior when its 
    // internal state changes. The object will appear 
    // to change its class.

    class tool{

    private:
      class state * current_;

    public:
      void set_current (state * s) { current_=s; };
      void on();
      void off();
    };

    class state{

    public:
      virtual void on(tool * t){ std::cout << " state on\n"; }
      virtual void off(tool *t){ std::cout << " state off\n"; }
    };

    void tool::on() 
    { std::cout << "on is the state"; current_->on(this); }
    void tool::off() 
    { std::cout << "off is the state"; current_->off(this); }
    
    class OFF : public state{  // changing state OFF->on
      
    public:
      void on (tool * t);
    };

    class ON : public state{  // changing state off->ON
      
    public:
      void off(tool * t){

	std::cout << "\tgoing from ON to OFF" << std::endl;
	t->set_current(new OFF());
	delete this;     // here I assume i am the one who destroy
      }
    };

    void OFF::on(tool * t){

      std::cout << "\tgoing from OFF to ON" << std::endl;
      t->set_current(new ON());
      delete this;      // here I assume i am the one who destroy
    }

  }; // end State


  namespace Strategy{
    
    // Strategy lets the algorithm vary independently 
    // from the clients that use it.

    enum ALGO { ALGO1, ALGO2 };

    class strategy{

    public:
      virtual void do_it() = 0;
    };

    class algo1 : public strategy{

      void do_it() { std::cout <<"\tcalling algo1"<<std::endl;}
    };

    class algo2 : public strategy{

      void do_it() { std::cout <<"\tcalling algo2"<<std::endl;}
    };

    
    class testbed{

    public: 

      testbed() : strategy_(NULL) {};
      void choose_strategy (unsigned int what)
      {
	strategy * tmp;

	switch (what){
	case ALGO1 : 
	  tmp = new algo1(); 
	  delete strategy_;
	  strategy_ = tmp;
	  break;
	case ALGO2 : 
	    tmp = new algo2();
	    delete strategy_;
	    strategy_ = tmp;
	    break;
	default:
	  strategy_ = new algo1(); break;
	}
      strategy_->do_it();
      }
    private:      
      strategy * strategy_;
    };   
  } // end Strategy

  namespace Template{
    
    // Define the skeleton of an algorithm 
    // deferring some steps to client subclasses
     
    class algorithm_base{

      void a() { std::cout << "\tA" << std::endl; }
      void b() { std::cout << "\tB" << std::endl; }
      void c() { std::cout << "\tC" << std::endl; }
      virtual void X() = 0;
      virtual void Y() = 0;

    public:

      void execute() { a(); X(); b();  Y(); c();}
    };
      
    class algorithm_refinement_first_model : public algorithm_base{
      
      void X() { std::cout << "\tX1" << std::endl; }
      void Y() { std::cout << "\tY1" << std::endl; }      
    };

    class algorithm_refinement_second_model :public algorithm_base{
      
      void X() { std::cout << "\tX2" << std::endl; }
      void Y() { std::cout << "\tY2" << std::endl; }      
    };

  } // end Template


  namespace Visitor{

    // Represent an operation to be performed on the elements 
    // of an object structure.  Operations are performed without 
    // polluting internal object

    // A practical result of this separation is the ability to add
    // new operations to existing object structures without modifying 
    // those structures.

    // In essence, the visitor allows one to add new virtual functions
    // to a family of classes without modifying the classes themselves; 

    class A;
    class B;
    class C;
    class Parent;

    // an interface for visitor

    struct parent_element_visitor{

      virtual void visit(A &a) const = 0;
      virtual void visit(B &b) const = 0;
      virtual void visit(C &c) const = 0;
      virtual void visit(Parent &p) const = 0;
      virtual ~parent_element_visitor() {};
    };

    // interface for a single element in hierarchy

    struct parent_element{

      virtual void accept (const parent_element_visitor& visitor) = 0;
      virtual ~parent_element() {};
    };

    // class in hierarchy

    class A : public parent_element{

    public:
      A() { std::cout << "\tcalled A" <<std::endl; }
      
      void accept(const parent_element_visitor & v)
      {
	v.visit(*this);
      }
    };

    // class in hierarchy

    class B : public parent_element{

    public:
      B() { std::cout << "\tcalled B" <<std::endl; }
      
      void accept(const parent_element_visitor & v)
      {
	v.visit(*this);
      }
    };

    // class in hierarchy

    class C : public parent_element{

    public:
      C() { std::cout << "\tcalled C" <<std::endl; }
      
      void accept(const parent_element_visitor & v)
      {
	v.visit(*this);
      }
    };

    // container of all the objects in hierarchy

    class Parent{

    public: 
      typedef std::vector<parent_element*>::const_iterator const_parent_collection_it;
      typedef std::vector<parent_element*> parent_collection;

      parent_collection& getElements()
      {
	return elements_;
      }

      Parent() 
      {
	elements_.push_back(new A());
	elements_.push_back(new B());
	elements_.push_back(new C());
      }
      ~Parent()
      {
	for (const_parent_collection_it it = elements_.begin(); 
	     it != elements_.end(); ++it)
	  { delete *it ; }                // call the destructors
      }

    private:
      parent_collection elements_;
    };


    // a first concrete implementation of visitor

    class parent_model_one_visitor : public parent_element_visitor{

    public:
      void visit(A &a) const { std::cout << "\tvisit A, model one" << std::endl;}
      void visit(B &b) const { std::cout << "\tvisit B, model one" << std::endl;}
      void visit(C &c) const { std::cout << "\tvisit B, model one" << std::endl;}

      void visit(Parent &p) const {

	Parent::parent_collection& elements = p.getElements();
	for (Parent::const_parent_collection_it it = elements.begin(); 
	     it != elements.end(); ++it){
	  
	  (*it)->accept(*this); // calling the visitor callback
	};
      }
    };

    // a second concrete implementation of visitor

    class parent_model_two_visitor : public parent_element_visitor{

    public:
      void visit(A &a) const { std::cout << "\tvisit A, model two" << std::endl;}
      void visit(B &b) const { std::cout << "\tvisit B, model two" << std::endl;}
      void visit(C &c) const { std::cout << "\tvisit B, model two" << std::endl;}

      void visit(Parent &p) const {

	Parent::parent_collection& elements = p.getElements();
	for (Parent::const_parent_collection_it it = elements.begin(); 
	     it != elements.end(); ++it){
	  
	  (*it)->accept(*this); // calling the visitor callback
	};
      }
    };

  };     // end visitor


  namespace Interpreter{

    // used to create grammars in C++
    //
    // I found this article, pretty inspiring
    //
    // http://www.peachpit.com/articles/article.aspx?p=467371
    //

    // http://www.peachpit.com/content/images/art_morris20_cinterpret/elementLinks/source.zip

  };

};

#endif
