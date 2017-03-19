package com.Animals;
import com.Abstract.Mammal;
/**
 * Класс Слон унаследованный от млекопитающего.
 * Содержит все необходимые методы и свойства,
 * характерные для этого животного
 */
public class Elephant extends Mammal {
    private String name = "Elephant";
    private int age = 5;

    /**
     * Метод вывода данных класса Слон
     * @return Строка сообщение для дальнейшего использования
     */
    public String outData(){
        String str;
        str = body + "Animal is: " + name + "\n" + "And it is " + age + " years old\nAnd have "+ foot + " feet";
        return str;
    }

    /**
     * Метод сообщения о том, что Слон поел
     * @return Строка сообщение о успешной еде слона
     */
    public String eat(){
        return "Elephant is eating!\n";
    }

    /**
     * Метод который возвращает имя слона
     * @return Строка с именем или породой слона
     */
    public String getSpiece(){
        return name;
    }
}
