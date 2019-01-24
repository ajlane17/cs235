/***********************************************************************
 * Header:
 *    Queue
 * Summary:
 *    This class contains the notion of a queue: a container that only 
 *    works by interacting with the first and last elements in the
 *    collection, with functionality that follows first-in-first-out.
 *
 *    This will contain the class definition of:
 *       queue          : similar to std::queue
 *       
 * Authors
 *    Adrian Lane, Ethan Holden
 ************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

// For debugging purposes
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

#include <cassert>

namespace custom
{
   /************************************************
    * QUEUE
    * A class that is a container using FIFO
    ***********************************************/
   template <class T>
   class queue
   {
      public:
         // Constructors and desctructors (inline)
         queue() : data(NULL), numPush(0), numPop(0), numCapacity(0)  {}
         queue(int numCapacity)                    throw (const char *):
          data(NULL), numPush(0), numPop(0), numCapacity(numCapacity) {}
        ~queue()                                     { delete [] data; }
         queue(const queue & rhs)                  throw (const char *):
            data(NULL), numPush(0), numPop(0), numCapacity(0)
            { if (!rhs.empty()) *this = rhs; }
        // Constructors (prototypes)
         queue & operator = (const queue & rhs)    throw (const char *);

         // standard container interfaces
         int size() const                 { return (numPush - numPop); }
         bool empty() const                    { return (size() == 0); }
         void clear()                      { numPop = 0; numPush = 0; };
         
         // Queue-specific interfaces
         void push(const T & t)                    throw (const char *);
         void pop()                                throw (const char *);
         T & front()                               throw (const char *);
         T front() const                           throw (const char *);
         T & back()                                throw (const char *);
         T back() const                            throw (const char *);
         

      private: 
         T * data;                   // dynamically allocated queue of T
         int numPush;              // The number of times push is called
         int numPop;                // The number of times pop is called
         int numCapacity;             // the total capacity of the queue

         // Resizes capacity to set size
         void resize(int newCapacity)              throw (const char *);
         int iHead() const            { return (numPop % numCapacity); }
         int iTail() const     { return ((numPush - 1) % numCapacity); }
            
   }; // QUEUE

   /********************************************
    * QUEUE :: ASSIGNMENT
    ********************************************/
   template <class T>
   queue <T> & queue <T> :: operator = (const queue <T> & rhs)
      throw (const char *)
   {
      // Reset head and tail
      numPush = 0;
      numPop = 0;

      if (numCapacity < rhs.size())
      {
         resize(rhs.size());
      }
      
      for (int i = rhs.numPop; i < rhs.numPush; i++)
      {
         push(rhs.data[i % numCapacity]);
      }

      std::cout << "assign -> cap : size : pop : push - " << numCapacity << " : " << size() << " : " << numPop << " : " << numPush << std::endl;
   }

   /********************************************
    * QUEUE :: PUSH
    ********************************************/
   template <class T>
   void queue <T> :: push(const T & t) throw (const char *)
   {
      std::cout << "start push -> cap : size : pop : push - " << numCapacity << " : " << size() << " : " << numPop << " : " << numPush << std::endl;

      if (size() == numCapacity)
      {
         resize(numCapacity * 2);
         std::cout << "push resized -> cap : size : pop : push - " << numCapacity << " : " << size() << " : " << numPop << " : " << numPush << std::endl;
      }

      std::cout << "after push -> cap : size : pop : push - " << numCapacity << " : " << size() << " : "<<  numPop << " : " << numPush << std::endl;

      numPush++;
      data[iTail()] = t;

      std::cout << "assign -> cap : size - " << numCapacity << " : " << size() << std::endl;
      std::cout << "assign -> pop : push - " << numPop << " : " << numPush << std::endl;
   }

   /********************************************
    * QUEUE :: POP
    ********************************************/
   template <class T>
   void queue <T> :: pop() throw (const char *)
   {
      if (!empty())
      {
         numPop++;
      }
   }

   /********************************************
    * QUEUE :: FRONT
    * Returns the first element
    ********************************************/
   template <class T>
   T & queue <T> :: front() throw (const char *)
   {
      if (empty())
         throw "ERROR: attempting to access an element in an empty queue";
      else
         return data[iHead()];
   }

   /********************************************
    * QUEUE :: FRONT (READ ONLY)
    * Returns a read-only version of the first element
    ********************************************/
   template <class T>
   T queue <T> :: front() const throw (const char *)
   {
      if (empty())
         throw "ERROR: attempting to access an element in an empty queue";
      else
         return data[iHead()];
   }

   /********************************************
    * QUEUE :: BACK
    * Returns the last element
    ********************************************/
   template <class T>
   T & queue <T> :: back() throw (const char *)
   {
      if (empty())
         throw "ERROR: attempting to access an element in an empty queue";
      else
         return data[iTail()];
   }

   /********************************************
    * QUEUE :: BACK (READ ONLY)
    * Returns a read-only version of the last element
    ********************************************/
   template <class T>
   T queue <T> :: back() const throw (const char *)
   {
      if (empty())
         throw "ERROR: attempting to access an element in an empty queue";
      else
         return data[iTail()];
   }

   /********************************************
    * QUEUE :: Resize
    * Resizes the capacity of the queue to the specified size
    ********************************************/
   template <class T>
   void queue <T> :: resize(int newCapacity) throw (const char *)
   {
      std::cout << "RESIZE CALLED" << std::endl;

      T *pNew;

      try
      {
         pNew = new T[newCapacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for queue";
      }

      for (int i = 0; i < size(); i++)
      {
         pNew[i] = front();
         pop();
      }

      numPop = 0;
      numPush = size();
      numCapacity = newCapacity;
      data = pNew;
   }

}; // namespace custom

#endif // QUEUE_H
