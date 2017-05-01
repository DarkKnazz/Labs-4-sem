package com.Animals;
import com.Abstract.Bird;
/**
 * Class Straus extends from abstract class Bird
 */
public class Straus extends Bird{
    private String name = "Straus";

    /**
     * Метод для отображения данных о птице на экран
     * @return Строка сообщение с данными о птице
     */
    public String outData(){
        String str;
        str = body + "Animal is: " + name + "\n" + "And have no wings\n";
        str += fly();
        return str;
    }

    /**
     * Метод говорящий о способности страуса летать
     * @return Строка сообщение для вывода на экран
     */
    public String fly(){
        return "Straus can't fly!\n";
    }

    /**
     * Метод сообщающий о процессе приема пищи у страуса
     * @return Строка сообщение о процессе еды
     */
    public String eat(){
        return "Straus is eating!\n";
    }

    /**
     * Метод получение имени страуса или названия вида
     * @return Строка сообщение с именем или видом страуса
     */
    public String getSpiece(){
        return name;
    }
}