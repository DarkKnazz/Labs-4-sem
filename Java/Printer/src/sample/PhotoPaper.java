package sample;

//Класс фотобумаги
public class PhotoPaper extends Paper{
    private String st = "Фотография на паспорт:)";
    private static boolean skin = true;

    //Метод изменения данных полей класса
    public void setSt(){
        if(skin)
            skin = false;
        else
            skin = true;
    }

    //Метод возврата в класс бумаги для вывода на экран
    public String getText(){
        String txt;
        if(skin)
            txt = "глянцевая";
        else
            txt = "матовая";
        String str = st + "\n" + "Поверхность: " + txt;
        return str;
    }
}