package sample;

//Класс бумаги, от которого наследуются еще три
//Метоы стандартные геттеры и сеттеры
public class Paper {
    protected static int height = 4;
    protected static int width = 3;
    private PhotoPaper photoPaper;
    private IT_Paper it_paper;

    public String Office_Work(){
        Office_Paper off = new Office_Paper();
        return off.getText();
    }

    public void setOffice(){
        Office_Paper off = new Office_Paper();
        off.setSt();
    }

    public String Photo_Work(){
        photoPaper = new PhotoPaper();
        return photoPaper.getText();
    }

    public void setPhoto(){
        photoPaper = new PhotoPaper();
        photoPaper.setSt();
    }

    public String ItWork(){
        it_paper = new IT_Paper();
        return it_paper.getText();
    }

    public void setIt(){
        it_paper = new IT_Paper();
        it_paper.setSt();
    }
}
