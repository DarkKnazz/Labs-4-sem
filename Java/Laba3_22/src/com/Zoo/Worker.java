package com.Zoo;
import com.Abstract.Animal;
/**
 * Класс рабочий зоопарка.
 * Необходим для уборки клеток и кормежки указанных животных
 */
public class Worker {

    /**
     * Метод накормить животное позволяет накормиьь выбранное животное и вывести строку об успешном выполнении дейтсвия
     * @param anim обьект класса Животное, содрежит заранее выбранного жителя зоопарка
     * @return Строка об успешном кормлении животного
     */
    public String feedAnimal(Animal anim){
        String str = anim.eat();
        return str;
    }

    /**
     * Метод почистить клетку позволяет работнику почистить клетку выбранного животного или птицы
     * @param anim обьект класса Животное, содрежит заранее выбранного жителя зоопарка
     * @return Строка об успешной уборке клетки определенного животного
     */
    public String cleanAnimal(Animal anim){
        String s1, itog = "";
        String temp = "I am cleaning the cage of ";
        s1 = anim.getSpiece();
        itog = itog + temp + s1 + "...\n";
        return itog;
    }
}
