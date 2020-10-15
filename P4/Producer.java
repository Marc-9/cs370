import java.util.Random;

public class Producer extends Thread{
    Buffer sharedBuffer;
    Random random = new Random();
    int runNum = 0;
    double runningCount = 0;
    public Producer(){

    }
    public Producer(Buffer sharedBuffer){
        this.sharedBuffer = sharedBuffer;
    }
    public void run(){
        while(runNum < 1000000){
            while(sharedBuffer.isFull){
                try {
                    sharedBuffer.wait();
                }
                catch(Exception e){ }
            }
            double ranNum = genRandomNum();
            runningCount += ranNum;
            try {
                sharedBuffer.insert(ranNum, runNum % 1000);
                ++runNum;
                sharedBuffer.notifyAll();
            }
            catch(Exception e){ }

            if(runNum % 100000 == 0){
                System.out.printf("Producer: Produced %,d items, Cumulative value of generated items=%.3f\n",runNum, runningCount);
            }
        }


    }

    private double genRandomNum(){
        return random.nextDouble() * 100.0;
    }
}
