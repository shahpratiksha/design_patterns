#include "design_patterns_creational.hpp"
#include "design_patterns_structural.hpp"
#include "design_patterns_behavioural.hpp"
  
void creational(void) {

  {
    using namespace Creational_Patterns::Abstract_Factory;
    
    std::cout << "Example of Abstract Factory" << std::endl;

    Widget * w1 = new OSX_Button;
    Widget * w2 = new Windows_Button;
    
    w1->draw();
    w2->draw();
  }

  {
    using namespace Creational_Patterns::Builder;
    
    std::cout << "Example of Builder" << std::endl;

    Build * b = new SimpleBuilder();
    ClientClass * c = new ClientClass(b);

    c;
  }

  {
    using namespace Creational_Patterns::Factory_Method;
    
    std::vector<Base *> factory;

    std::cout << "Example of Factory" << std::endl;

    // here you can have multiple choices deferred to this level

    factory.push_back(new A);
    factory.push_back(new B);
  }

  {
    using namespace Creational_Patterns::Object_Pool;
    
    std::cout << "Example of Object Pool" << std::endl;

    Pool pool;
    pool.getObject();
  }

  {
    using namespace Creational_Patterns::Prototype;
   
    std::cout << "Example of Proto" << std::endl;

    Proto * collection[num_protos_];
 
    collection[0] = Proto::findAClone(type_a);
    std::cout << "\t type_a found the expected type=" << 
      (collection[0]->returnType()==type_a ? "yes" : "no" ) << std::endl;

    collection[1] = Proto::findAClone(type_b);
    std::cout << "\t type_b found the expected type=" << 
      (collection[0]->returnType()==type_b ? "yes" : "no" ) << std::endl;
  
  }

  {
    using namespace Creational_Patterns::Singleton;
   
    std::cout << "Example of Singleton" << std::endl;

    for (unsigned int i = 0 ; i < 100 ; ++i)
      Single::getInstance();
  }

}

void structural(void){

 {
    using namespace Structural_Patterns::Adapter;
   
    std::cout << "Example of Adapter" << std::endl;

    adapter * ada = new adapter();
    ada->make();
 }

 {
    using namespace Structural_Patterns::Bridge;
   
    std::cout << "Example of Bridge" << std::endl;

    bridge * b1 = new a();
    bridge * b2 = new b();
 }

 {
    using namespace Structural_Patterns::Composite;
   
    std::cout << "Example of Composite" << std::endl;

    Composite containers[10];

    // adding all the leaf under 0

    for (unsigned int i = 1 ; i < 10 ; i++){
      containers[i].add(new Leaf(i));
      containers[0].add(&(containers[i]));
    }
    
    std::cout << "\t";
    containers[0].traverse();
    std::cout << std::endl;
 }

 {
   using namespace Structural_Patterns::Decorator;

   std::cout << "Example of Decorator" << std::endl;

   A_and_X ax;
   ax.make();
 }

 {
   using namespace Structural_Patterns::Facade;

   std::cout << "Example of Facade" << std::endl;
   facade f;
 }

 {
   using namespace Structural_Patterns::Flyweight;

   std::cout << "Example of Flyweight" << std::endl;

   Icon * i0 = FlyweightFactory::getIcon(0);
   Icon * i1 = FlyweightFactory::getIcon(1);
   Icon * i2 = FlyweightFactory::getIcon(0);


   // note that here i am reusing in a flyweight manner the icon with name 0
 }

 {
   using namespace Structural_Patterns::Proxy;
   std::cout << "Example of Proxy" << std::endl;

   Image image[10];

   image[0].draw();
   image[0].draw();

   image[1].draw();
 }

}

void behavioural(){


  {
    using  namespace Behavioural_Patterns::Chain_Of_Responsability;
    
    std::cout << "Example of Chain of Responsability" << std::endl;

    H1 root(1);
    H1 h1(2);
    H2 h2(3);
    root.add(&h1);
    root.add(&h2);
    root.handle(3);
  }

  {
    using  namespace Behavioural_Patterns::Command;
    
    std::cout << "Example of Command" << std::endl;

    client c; 
    command * com =        // registerig the specific command
      new a_specific_command(&c, &client::client_function);
    com->execute(3);
  }

  {
    using  namespace Behavioural_Patterns::Iterator;

    std::cout << "Example of Iterator" << std::endl;

    stack s;

    for (int i = 1; i < 10; i++)
      s.push(i);
    s.pop();

    iterator it(s);
    
    for (int i = 0; it() ; ++i, ++it)
      { std::cout << "\ti=" << i << " " 
		  << *it << " " << std::endl; }
  }

  {
    using  namespace Behavioural_Patterns::Mediator;

    std::cout << "Example of Mediator" << std::endl;

    list l;
    node a(1), b(2), c(3), d(4);

    std::cout << "\tList mediates between nodes" 
	      << std::endl << "\t";

    l.add(&a);
    l.add(&b);
    l.add(&c);
    l.add(&d);
    l.traverse();
  }

  { 
    using  namespace Behavioural_Patterns::Memento;

    std::cout << "Example of Memento" << std::endl;    

    client c(10);
    memento * m = c.create_memento();
    c.increment();
    c.restore_from_memento(m);  // undo
    
    std::cout << "\t incrementing 10 and restoring from memento c=" <<
      c.get_value() << std::endl;
  }

  { 
    using  namespace Behavioural_Patterns::Observer;

    std::cout << "Example of Observer" << std::endl;    
    
    a_observer a_o;
    b_observer b_o;
    
    subject s;

    s.attach(&a_o);
    s.attach(&b_o);

    s.set_value(10);

  }

  { 
    using  namespace Behavioural_Patterns::State;
    
    std::cout << "Example of State" << std::endl;    

    tool t;

    OFF * off_state = new OFF();
    ON * on_state = new ON();

    std::cout << "\tcreating on state" << std::endl;

    t.set_current(on_state);
    on_state->off(&t);

    std::cout << "\tcreating off state" << std::endl;

    t.set_current(off_state);
    off_state->on(&t);    

  }
    
  {
    using  namespace Behavioural_Patterns::Strategy;

    std::cout << "Example of Strategy" << std::endl;    
    
    testbed ts;
    
    ts.choose_strategy(ALGO1);
    ts.choose_strategy(ALGO2);
  }

  {
    using  namespace Behavioural_Patterns::Template;

    std::cout << "Example of Template" << std::endl;    
    
    algorithm_refinement_first_model a1;
    algorithm_refinement_second_model a2;

    std::cout << "Executing algorithm 1" << std::endl;
    a1.execute();

    std::cout << "Executing algorithm 2" << std::endl;
    a2.execute();
  }

  {
    using  namespace Behavioural_Patterns::Visitor;

    std::cout << "Example of Visitor" << std::endl;    

    Parent p;
    parent_model_one_visitor vis1;
    parent_model_two_visitor vis2;

    vis1.visit(p);
    vis2.visit(p);
  };
}



int main(){

  creational();
  structural();
  behavioural();
}
