package sample;

public class MyThread extends Thread {
    double tempScore;
    int h;
    double firstOsn;
    double secondOsn;
    public MyThread(int a, int b, double c, double d){
        h = b - a;
        firstOsn = c;
        secondOsn = d;
    }
    public void run() {
        tempScore = (firstOsn + secondOsn)/2 * h;
    }

    double getData(){
        return tempScore;
    }
}