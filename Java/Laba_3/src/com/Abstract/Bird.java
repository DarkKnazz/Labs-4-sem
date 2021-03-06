package com.Abstract;
/**
 * Абстрактный класс птицы унаследованный от абстрактного класса Животное
 * Содержит более характерный метод для птиц
 */
abstract public class Bird extends Animal{
    protected int wings = 2;

    /**
     * Метод, который показывает способность летать птицы
     * @return Строка сообщение о способности летать
     */
    public String fly(){
        return "It can fly!\n";
    }

    /**
     * Метод, означающий процесс еды Птицы
     * @return Строка сообщение о том, что Птица поела
     */
    public String eat(){
        return "Mammal is eating!";
    }
}
