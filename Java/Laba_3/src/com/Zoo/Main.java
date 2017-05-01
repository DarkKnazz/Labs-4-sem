package com.Zoo;
import com.Abstract.Animal;
import com.Watcher.Watcher;
import com.Animals.*;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.*;
import org.eclipse.swt.layout.*;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.*;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Label;
import java.util.ArrayList;

/**
 * Главный класс, в котором находятся обьект зоопарка и зрителя,
 * который может получать случайное животное для наблюдения.
 * Также здесь создаются обьекты сцены и компонуются с помощью сетки
 */
public class Main {
    public static void main(String[] args) {
        Zoo zoo = new Zoo();
        Watcher watcher = new Watcher();

        ArrayList<Animal> animals = new ArrayList<Animal>();
        animals.add(new Elephant());
        animals.add(new Tiger());
        animals.add(new Flamingo());
        animals.add(new Straus());

        Display display = new Display();
        Shell shell = new Shell(display, SWT.CLOSE | SWT.TITLE);
        shell.setText("Zoo");
        shell.setLayout(new GridLayout(2, false));

        Label wtchr = new Label(shell, SWT.NONE);
        wtchr.setText("Watcher");
        GridData gridData = new GridData();
        gridData.horizontalAlignment = SWT.CENTER;
        gridData.horizontalSpan = 1;
        wtchr.setLayoutData(gridData);

        Label anml = new Label(shell, SWT.NONE);
        anml.setText("Animal");
        gridData = new GridData();
        gridData.grabExcessHorizontalSpace = true;
        gridData.horizontalAlignment = SWT.CENTER;
        gridData.horizontalSpan = 1;
        anml.setLayoutData(gridData);

        Button wtchrButton = new Button(shell, SWT.NONE);
        wtchrButton.setText("Look at animal");
        gridData = new GridData();
        gridData.widthHint = 100;
        gridData.verticalAlignment = SWT.TOP;
        wtchrButton.setLayoutData(gridData);

        Text addressText = new Text(shell, SWT.BORDER | SWT.WRAP | SWT.MULTI);
        gridData = new GridData();
        gridData.horizontalAlignment = SWT.FILL;
        addressText.setLayoutData(gridData);
        addressText.setText("\n\n\n\n\n");

        Label wrkr = new Label(shell, SWT.NONE);
        wrkr.setText("Worker");
        gridData = new GridData();
        gridData.horizontalAlignment = SWT.CENTER;
        gridData.horizontalSpan = 1;
        wrkr.setLayoutData(gridData);

        Label space = new Label(shell, SWT.NONE);
        gridData = new GridData();
        gridData.horizontalAlignment = SWT.CENTER;
        gridData.horizontalSpan = 1;
        space.setLayoutData(gridData);

        Button wrkrButton = new Button(shell, SWT.NONE);
        wrkrButton.setText("Feed");
        gridData = new GridData();
        gridData.horizontalAlignment = SWT.CENTER;
        gridData.widthHint = 100;
        gridData.verticalAlignment = SWT.TOP;
        wrkrButton.setLayoutData(gridData);

        final Combo c = new Combo(shell, SWT.READ_ONLY);
        String items[] = { "Elephant", "Flamingo", "Tiger", "Straus" };
        c.setItems(items);
        gridData = new GridData();
        gridData.horizontalAlignment = SWT.FILL;
        c.setLayoutData(gridData);

        Button clnButton = new Button(shell, SWT.NONE);
        clnButton.setText("Clean the cage");
        gridData = new GridData();
        gridData.horizontalAlignment = SWT.CENTER;
        gridData.widthHint = 100;
        gridData.verticalAlignment = SWT.TOP;
        gridData.horizontalSpan = 1;
        clnButton.setLayoutData(gridData);

        space.setLayoutData(gridData);

        shell.pack();
        Animal anim = new Elephant();

        wtchrButton.addSelectionListener(new SelectionAdapter() {
            public void widgetSelected(SelectionEvent e) {
                String st;
                st = zoo.serveWatcher(watcher);
                addressText.setText(st);
            }
        });

        wrkrButton.addSelectionListener(new SelectionAdapter() {
            public void widgetSelected(SelectionEvent e) {
                String str = c.getText();
                String st;
                if(str != ""){
                    switch(str){
                        case "Elephant":{
                            st = zoo.getWorker().feedAnimal(animals.get(0));
                            addressText.setText(st);
                        }break;
                        case "Tiger":{
                            st = zoo.getWorker().feedAnimal(animals.get(1));
                            addressText.setText(st);
                        }break;
                        case "Straus":{
                            st = zoo.getWorker().feedAnimal(animals.get(3));
                            addressText.setText(st);
                        }break;
                        case "Flamingo":{
                            st = zoo.getWorker().feedAnimal(animals.get(2));
                            addressText.setText(st);
                        }break;
                    }
                }
            }
        });

        clnButton.addSelectionListener(new SelectionAdapter() {
            public void widgetSelected(SelectionEvent e) {
                String s1 = c.getText();
                String s2;
                if(s1 != ""){
                    switch(s1){
                        case "Elephant":{
                            s2 = zoo.getWorker().cleanAnimal(animals.get(0));
                            addressText.setText(s2);
                        }break;
                        case "Tiger":{
                            s2 = zoo.getWorker().cleanAnimal(animals.get(1));
                            addressText.setText(s2);
                        }break;
                        case "Straus":{
                            s2 = zoo.getWorker().cleanAnimal(animals.get(3));
                            addressText.setText(s2);
                        }break;
                        case "Flamingo":{
                            s2 = zoo.getWorker().cleanAnimal(animals.get(2));
                            addressText.setText(s2);
                        }break;
                    }
                }
            }
        });
        shell.setSize(280, 260);
        shell.open();
        while (!shell.isDisposed()) {
            if (!display.readAndDispatch())
                display.sleep();
        }
        shell.dispose();
        display.dispose();
    }
}
