package sample;
//Класс офисной бумаги
public class Office_Paper extends Paper{
    private String st = "Офисная бумага А4";

    //Метод изменения данных бумаги
    public void setSt(){
        height++;
        width +=2;
    }

    //Метод возврата приватных данных для вывода
    public String getText(){
        String str = st + "\n" + "Ширина: " + width + "\nВысота: " + height;
        return str;
    }
}
