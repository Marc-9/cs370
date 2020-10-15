public class ProducerConsumer {

        public static void main(String[] args){
            Buffer sharedBuffer = new Buffer();
            Producer myProducer = new Producer(sharedBuffer);
            Consumer myConsumer = new Consumer(sharedBuffer);
            myProducer.start();
            myConsumer.start();
            while(myProducer.isAlive() || myConsumer.isAlive()){

            }
            System.out.printf("Producer: Finished generating %,d items\n", myProducer.runNum);
            System.out.printf("Consumer: Finished consuming %,d items\n", myConsumer.runNum);
            System.out.println("Exiting!");
        }
}
