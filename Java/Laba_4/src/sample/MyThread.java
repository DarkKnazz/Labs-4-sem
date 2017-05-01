package sample;

/**
 * Another thread that extends from Thread
 */
public class MyThread extends Thread {
    double tempScore;
    int h;
    double firstOsn;
    double secondOsn;
    public MyThread(){

    }

    /**
     * Constructor taking data about trapeciya
     * @param a left height
     * @param b right height
     * @param c first side
     * @param d second side
     */
    public MyThread(int a, int b, double c, double d){
        h = b - a;
        firstOsn = c;
        secondOsn = d;
    }

    /**
     * Method for counting the area
     */
    public void run() {
        tempScore = (firstOsn + secondOsn)/2 * h;
    }

    /**
     * Method for returning area of trapeciya
     * @return area of trapeciya
     */
    double getData(){
        return tempScore;
    }
}