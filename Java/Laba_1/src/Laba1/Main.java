package Laba1;
import javax.swing.*;

import java.awt.*;
import java.awt.event.*;

public class Main extends JFrame
{
    // Текстовые поля
    JTextField word, letter;
    JLabel label1, label2, label3;
    JButton button;

    public Main()
    {
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        // Создание текстовых полей и кнопок
        word = new JTextField(15);
        label1 = new JLabel("Слово");
        letter = new JTextField(15);
        label2 = new JLabel("Буква ");
        button = new JButton("Посчитать");
        label3 = new JLabel();
        // Слушатель окончания ввода
        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String str_Word = word.getText();
                String str_Let = letter.getText();
                int kol = 0;
                if(str_Let.length() > 1)
                    label3.setText("> 1 буквы");
                else{
                    for(char element : str_Word.toCharArray()){
                        if(element == str_Let.charAt(0))
                            kol++;
                    }
                    if(kol == 0)
                        label3.setText("Не входит!!!!");
                    else
                        label3.setText(String.valueOf(kol));
                }
            }
        });
        button.setPreferredSize(new Dimension(100,22));
        // Создание панели с текстовыми полями
        JPanel contents = new JPanel(new FlowLayout(FlowLayout.LEFT));
        contents.add(label1);
        contents.add(word);
        contents.add(label2);
        contents.add(letter);
        contents.add(button);
        contents.add(label3);
        setContentPane(contents);
        // Определяем размер окна и выводим его на экран
        setSize(240, 100);
        setVisible(true);
        setTitle("Program 1");
        setResizable(false);
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        int locationX = screenSize.width / 2-50;
        int locationY = screenSize.height / 2-50;
        setBounds(locationX, locationY, 240, 130);
    }
    public static void main(String[] args) {
        new Main();
    }
}
