package sample;

/**
 * Created by Knazz on 01.04.2017.
 */
public class MyThread extends Thread {
    public int parametr;
    public MyThread(int parametr) {
        this.parametr = parametr;
    }
    public void run() {
        System.out.println("parametr is " + parametr);
        //отправка запроса
        //........
    }

    int getData(){
        return parametr;
    }
}