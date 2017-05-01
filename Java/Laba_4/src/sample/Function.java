package sample;

/**
 * Class for counting in diapazone
 */

public class Function {
    private MyThread thread;
    private int begin;
    private int end;
    private int func;
    private double score;

    /**
     * Constructr of class
     * @param a left diapazone
     * @param b right diapazone
     * @param c number of function
     * @param thr object of thread for counting
     */

    public Function(int a, int b, int c, MyThread thr){
        begin = a;
        end = b;
        func = c;
        thread = thr;
    }

    /**
     * Method of taking the score
     * @return Result of counting
     */
    public double getScore(){
        return score;
    }

    /**
     * Incrementing score
     */
    public void incScore(){
        score += thread.getData();
    }

    /**
     * Method for counting integral.
     * Data is given to thread
     */
    public void countIntegral(){
        int beginCycle;
        int endCycle;
        double tempA = 0;
        double tempB = 0;
        if(begin > end) {
            beginCycle = end;
            endCycle = begin;
        } else{
            beginCycle = begin;
            endCycle = end;
        }

        for(int i = beginCycle; i < endCycle; i++){
            switch(func){
                case 1:{
                    tempA = Math.sin(i);
                    tempB = Math.sin(i+1);
                }break;
                case 2:{
                    tempA = Math.cos(i);
                    tempB = Math.cos(i+1);
                }break;
                case 3:{
                    tempA = (i*Math.PI)/2;
                    tempB = ((i+1)*Math.PI)/2;

                }break;
                case 4:{
                    tempA = i*i + (3*i);
                    tempB = (i+1)*(i+1) + (3*(i+1));
                }break;
            }
            thread = new MyThread(i, i+1, tempA, tempB);
            thread.start();
            try {

                thread.join();
                incScore();
                // действия после завершения работы потока
            } catch (InterruptedException x) {}
        }
    }
}
