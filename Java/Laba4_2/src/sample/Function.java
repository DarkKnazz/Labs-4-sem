package sample;

public class Function {
    private MyThread thread;
    private int begin;
    private int end;
    private int func;
    private double score;

    public Function(int a, int b, int c){
        begin = a;
        end = b;
        func = c;
    }

    public double getScore(){
        return score;
    }

    public void incScore(){
        score += thread.getData();
    }

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
                    tempA = Math.sqrt(i) + (3*i);
                    tempB = Math.sqrt(i+1) + (3*(i+1));
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
