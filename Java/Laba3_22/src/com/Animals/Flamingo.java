package com.Animals;
import com.Abstract.Bird;
/**
 * Class Flamingo extends from abstract class Bird
 */
public class Flamingo extends Bird{
    private String name = "Flamingo";
    private int age = 3;

    /**
     * Метод для отображения данных о птице на экран
     * @return Строка сообщение с данными о птице
     */
    public String outData(){
        String str;
        str = body + "Animal is: " + name + "\n" + "And it is " + age + " years old\nAnd have "+ wings + " wings\n";
        str += fly();
        return str;
    }

    /**
     * Метод говорящий о способности фламинго летать
     * @return Строка сообщение для вывода на экран
     */
    public String fly(){
        return "Flamingo can fly!\n";
    }

    /**
     * Метод сообщающий о процессе приема пищи у Фламинго
     * @return Строка сообщение о процессе еды
     */
    public String eat(){
        return "Flamingo is eating!\n";
    }

    /**
     * Метод получение имени фламинго или названия вида
     * @return Строка сообщение с именем или видом фламинго
     */
    public String getSpiece(){
        return name;
    }
}
