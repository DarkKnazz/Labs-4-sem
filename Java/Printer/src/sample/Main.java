package sample;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.*;
import javafx.stage.Stage;

public class Main extends Application {
    public boolean printing = false;
    public Paper paper = new Paper();
    public Printer printer;
    @Override
    public void start(Stage primaryStage) throws Exception {
        HBox header = new HBox();
        HBox list = new HBox();
        HBox Change = new HBox();
        VBox root = new VBox();
        root.getStylesheets().add
                (Main.class.getResource("app.css").toExternalForm());
        TextArea textArea = new TextArea();
        Label lbl = new Label("Заправить бумагой");

        ObservableList<String> options =
                FXCollections.observableArrayList(
                        "Офисная бумага",
                        "Фотобумага",
                        "Чертежная бумага"
                );
        final ComboBox comboBox = new ComboBox(options);

        ObservableList<String> changeList =
                FXCollections.observableArrayList(
                        "Офисная бумага",
                        "Фотобумага",
                        "Чертежная бумага"
                );
        final ComboBox comboChange = new ComboBox(changeList);

        Button button1 = new Button("OK");
        Button button2 = new Button("Печать");
        Button button_Change = new Button("Изменить");

        //Заголовок
        header.setPadding(new Insets(0, 0, 0, 0));
        header.setSpacing(41);
        header.getChildren().addAll(lbl,button1);

        //Выбор бумаги для печати
        list.getChildren().add(comboBox);
        list.getChildren().add(button2);
        list.setSpacing(30);
        list.setPadding(new Insets(20, 0, 20, 0));

        //Создание поля для вывода
        textArea.setPrefRowCount(3);
        textArea.setWrapText(true);

        //Создание формы для изменения
        Change.getChildren().add(comboChange);
        Change.getChildren().add(button_Change);
        Change.setSpacing(30);
        Change.setPadding(new Insets(20, 0, 5, 0));

        //Создание сцены
        root.setPadding(new Insets(20, 20, 15, 15));
        root.getChildren().add(header);
        root.getChildren().add(list);
        root.getChildren().add(textArea);
        root.getChildren().add(Change);
        primaryStage.setTitle("Printer");
        primaryStage.setScene(new Scene(root, 310, 275));
        primaryStage.setResizable(false);
        primaryStage.show();

        //Обработчики событий кнопок
        button1.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                printing = true;
                printer = new Printer(paper);
            }
        });

        //Обработка кнопки для вывода содержимого бумаги
        button2.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                String str;
                if(printing == true){
                    String st = comboBox.getValue().toString();
                    textArea.setText(st);
                    switch (st){
                        case "Офисная бумага":{
                            str = printer.getOffice();
                            textArea.setText(str);
                        } break;

                        case "Фотобумага": {
                            str = printer.getPhoto();
                            textArea.setText(str);
                        }break;

                        case "Чертежная бумага": {
                            str = printer.getIT();
                            textArea.setText(str);
                        }break;
                    }
                }
            }
        });

        //Обработка кнопки для изменения данных вида бумаги
        button_Change.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                if(printing == true){
                    String st = comboChange.getValue().toString();
                    switch (st){
                        case "Офисная бумага":{
                            printer.setOffice();
                        } break;

                        case "Фотобумага":{
                            printer.setPhoto();
                        } break;

                        case "Чертежная бумага":{
                            printer.setIT();
                        } break;
                    }
                }
            }
        });
    }


    public static void main(String[] args) {
        launch(args);
    }
}
