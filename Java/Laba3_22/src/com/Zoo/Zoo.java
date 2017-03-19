package com.Zoo;
import com.Watcher.Watcher;
import com.Abstract.Animal;
import com.Animals.*;
/**
 * Класс Зоопарк, место обитания рабочих и животных
 * поля класса это обьект рабочего и животного
 */
public class Zoo {
    public Worker worker = new Worker();
    public Animal anim;

    /**
     * Метод получить рабочего возвращает обьект класса Рабочий для дальнейшей работы с ним
     * @return Обьект класса Worker
     */
    public Worker getWorker(){
        return worker;
    }

    /**
     * Метод для случайной генерации животного для зрителя
     * @return Обьект сгенерированного класса Животное
     */
    public Animal randAnim(){
        int a = 1;
        int b = 4;
        int randomNumber = a + (int)(Math.random()*b);
        Animal temp;
        if(randomNumber == 1)
            temp = new Elephant();
        else if(randomNumber == 2)
            temp = new Flamingo();
        else if(randomNumber == 3)
            temp = new Tiger();
        else if(randomNumber == 4)
            temp = new Straus();
        else
            temp = new Elephant();
        return temp;
    }

    /**
     * Метод обслужить Зрителя выведет в консоль строку о проведении данной операции
     * @return str Строка с сообщением о просмотре зрителем животных
     */
    public String serveWatcher(Watcher watcher){
        Animal anim = randAnim();
        String str = watcher.lookAtAnimal(anim);
        return str;
    }

}
