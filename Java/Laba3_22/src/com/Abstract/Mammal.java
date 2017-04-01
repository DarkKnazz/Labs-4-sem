package com.Abstract;
/**
 * Абстрактный класс Млекопитающего.
 * Содержит методы, характерные для более узкого круга животных.
 * Содержит свойство количества ног
 */
abstract public class Mammal extends Animal{
    protected int foot = 4;
    /**
     * Метод, означающий процесс еды Млекопитающего
     * @return Строка сообщение о том, что Млекопитающее поело
     */
    public String eat(){
        return "Mammal is eating!";
    }
}
