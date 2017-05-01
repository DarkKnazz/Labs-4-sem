package com.Abstract;
/**
 * Абстрактный класс животного,
 * общий для всех животных,
 * также обладает всеми необходимыми общими свойствами
 */
abstract public class Animal {
    protected String body = "Animal has a body!\n";

    /**
     * Метод, означающий процесс еды животного
     * @return Строка сообщение о том, что животное поело
     */
    public String eat(){
        return "Animal is eating!";
    }

    /**
     * Метод вывода данных обьекта класса
     * @return Строка с данными из полей класса
     */
    public String outData(){
        return body;
    }

    /**
     * Метод, возвращающий вид или название животного на экран
     * @return Строка сообщение с видом животного
     */
    public String getSpiece(){
        return body;
    }
}
