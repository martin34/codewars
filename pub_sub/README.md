### Todos:
* Currently a pointer is passed to the instance, which should be send. This could be a problem in an multithreaded environment, because the pointer could be invalidated during the sending procedure.
* The pipl pattern is used, to create a Subscriber fasade, which is easy to use. Since I added support for multiple types, it is necessary to call an additional function after the creating of the subscriber. This should could be done in a factory function or in the implementation of the subscriber.
* Every publisher asks the registry for the subscriber, before it sends. There are multiple possibilities to improve this: 
  - During the creation of a publisher or subscriber, they register themself in the registry --> The registry provides the publisher with updates, if necessary (e. g. a new subsriber for its port is added)
  - All connections could be fixed at compile time and known to the registry --> Registry could be a factory for publisher and subscriber. It would be not necessary to have runtime polymorphism. 
* Currently only one subscriber per publisher is supported. --> Add more ...
