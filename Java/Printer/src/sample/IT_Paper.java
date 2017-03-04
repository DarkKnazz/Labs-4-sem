package sample;

//Класс чертежной бумаги
public class IT_Paper extends Paper{
    private String st = "Чертежная бумага";
    private static String s = "A1(Ватман)";

    //Метод изменения полей класса
    public void setSt(){
        if(s == "A1(Ватман)")
            s = "A3(Для курсача)";
        else
            s = "A1(Ватман)";
    }

    //Метод возврата текста для вывода на экран
    public String getText(){
        String str = st +" " + s +  "\n" + "Ширина: " + width + "\nВысота: " + height;
        return str;
    }
}
