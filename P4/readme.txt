README
======

This package includes the following files.

|-- Buffer.class [The buffer class that will be accessed by both the Producer and the Consumer. Max-Size of 1000]
|-- Producer.class [Produces random numbers to be entered into the Buffer until the Buffer is full (or Context Switched)]
|-- Consumer.class [Consumes elements from the Buffer until the Buffer is empty (or context switched)]
|-- ProducerConsumer.class [The main file that creates instances of Producer/Consumer/Buffer and starts the threads]
|-- README.txt [This file]

To compile:
    make

To run:
    make run

To clean:
    make clean
