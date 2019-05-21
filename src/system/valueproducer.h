#ifndef _value_producer_H_
#define _value_producer_H_

#include "observable.h"
#include <ArduinoJson.h>
#include "valueconsumer.h"

/**
 * A ValueProducer<> is any device or piece of code that outputs a value for consumption
 * elsewhere.  They are Observable, allowing code to be notified whenever a new value
 * is available.  They can be connected directly to ValueConsumers of the same type
 * using the connectTo() method.
 */
template <typename T>
class ValueProducer : virtual public Observable {

    public:
        /**
         *  Constructor
         * @param valueIdx Consumers can have one or more inputs feeding them
         *   This parameter allows you to specify which input number this producer
         *   is connecting to. For single input consumers, leave the index at
         *   zero.
         *  @see ValueConsumer::set_input()
         */
        ValueProducer() {}

        virtual T get() { return output; }

        void connectTo(ValueConsumer<T>* pConsumer, uint8_t valueIdx) {
            this->attach([this, pConsumer, valueIdx](){
                pConsumer->set_input(this->get(), valueIdx);
            });
        }

    protected:
        T output;
};

// The following common types are defined using #define to make the purpose of a template class
// clearer, as well as allow for interoperability between the various classes. If NumericProducer
// inherited from "ValueProducer<float>"" vs just being an alias, it would actually be a different type than
// anything defined as being or inheriting from "ValueProducer<float>"".  When used as an alias, they
// are interchangable.
#define NumericProducer ValueProducer<float> 
#define IntegerProducer ValueProducer<int> 
#define BooleanProducer ValueProducer<bool>
#define StringProducer  ValueProducer<String> 

#endif