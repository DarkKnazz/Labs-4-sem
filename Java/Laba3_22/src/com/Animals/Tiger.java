package com.Animals;
import com.Abstract.Mammal;
/**
 * Класс Тигр унаследованный от млекопитающего.
 * Содержит все необходимые методы и свойства,
 * характерные для этого животного
 */
public class Tiger extends Mammal {
    private String name = "Tiger";
    private int age = 10;

    /**
     * Метод вывода данных класса Тигр
     * @return Строка сообщение для дальнейшего использования
     */
    public String outData(){
        String str;
        str = body + "Animal is: " + name + "\n" + "And it is " + age + " years old\nAnd have "+ foot + " feet";
        return str;
    }

    /**
     * Метод сообщения о том, что Тигр поел
     * @return Строка сообщение о успешной еде тигра
     */
    public String eat(){
        return "Tiger is eating!\n";
    }

    /**
     * Метод который возвращает имя тигра
     * @return Строка с именем или видом тигра
     */
    public String getSpiece(){
        return name;
    }
}
