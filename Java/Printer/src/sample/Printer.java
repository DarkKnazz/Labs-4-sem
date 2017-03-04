package sample;
//Класс принтера, в который загружается бумага
public class Printer {
    private static Paper pape;
    //Конструктор производит "загрузку" бумаги в принтер
    public Printer(Paper paper){
        pape = paper;
    }

    //Метод для вывода текста класса офисной бумаги
    public String getOffice(){
        return pape.Office_Work();
    }

    //Метод для вывода текста класса фотобумаги
    public String getPhoto(){
        return pape.Photo_Work();
    }

    //Метод для вывода текста класса чертежной бумаги
    public String getIT(){
        return pape.ItWork();
    }

    //Метод для изменения офисной бумаги
    public void setOffice(){
        pape.setOffice();
    }

    //Метод для изменения фотобумаги
    public void setPhoto(){
        pape.setPhoto();
    }

    //Метод для изменения чертежной бумаги
    public void setIT(){
        pape.setIt();
    }
}
