public class Buffer {
    boolean isEmpty = true;
    boolean isFull = false;
    int size = 0;
    double[] sharedBuffer = new double[1000];

    public synchronized void sizeAlterationsInsert(){
        if(this.isEmpty){
            this.isEmpty = false;
        }
        if(++this.size == 1000){
            this.isFull = true;
        }

    }

    public synchronized void sizeAlterationsRemove(){
        if(this.isFull){
            this.isFull = false;
        }
        if(--this.size == 0){
            this.isEmpty = true;
        }
    }

    public synchronized void insert(double food, int position) throws InterruptedException{
        sizeAlterationsInsert();
        sharedBuffer[position] = food;
    }

    public synchronized double remove(int position) throws InterruptedException{
        sizeAlterationsRemove();
        return sharedBuffer[position];
    }

}
