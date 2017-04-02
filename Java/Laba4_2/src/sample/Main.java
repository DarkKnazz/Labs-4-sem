package sample;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;

public class Main extends Application {

    private Function func;

    int score = 0;
    @Override
    public void start(Stage primaryStage) throws Exception{
        VBox root = new VBox();
        HBox header = new HBox();
        HBox diap = new HBox();
        HBox answer = new HBox();
        HBox choose = new HBox();
        HBox butt = new HBox();

        Label head = new Label("Integral calculator");
        head.setPadding(new Insets(0, 0, 10, 105));
        header.setId("header");
        header.getChildren().add(head);

        Label begin = new Label(" A: ");
        Label end = new Label(" B: ");
        begin.setId("begin");
        end.setId("end");
        TextField textA = new TextField();
        TextField textB = new TextField();
        textA.setId("textA");
        textB.setId("textB");
        diap.setPadding(new Insets(20, 0, 20, 0));
        diap.getChildren().addAll(begin, textA, end, textB);

        Label ans = new Label(" Answer:   ");
        TextField textAns = new TextField();
        answer.getChildren().addAll(ans, textAns);
        answer.setPadding(new Insets(10, 20, 20, 30));

        Label chLbl = new Label(" Choose function:   ");
        ObservableList<String> options =
                FXCollections.observableArrayList(
                        "1. f(x) = sin x",
                        "2. f(x) = cos x",
                        "3. f(x) = (x*Pi)/2",
                        "4. f(x) = x^2 + 3*x"
                );
        ComboBox comboBox = new ComboBox(options);
        choose.getChildren().addAll(chLbl, comboBox);
        choose.setPadding(new Insets(10, 20, 20, 30));

        Button button = new Button("Calculate");
        butt.setPadding(new Insets(0, 0, 0, 30));
        butt.getChildren().add(button);

        root.getStylesheets().add((getClass().getResource("style.css")).toExternalForm());
        root.setPadding(new Insets(10, 0, 20, 0));
        root.getChildren().addAll(header, diap, answer, choose, butt);
        primaryStage.setTitle("Integral counter");
        System.out.println(score);
        primaryStage.setScene(new Scene(root, 360, 300));
        primaryStage.show();

        button.addEventHandler(MouseEvent.MOUSE_CLICKED, new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent mouseEvent) {
                button.setDisable(true);
                int i;
                String A, B, f;
                A = textA.getText();
                B = textB.getText();
                f = comboBox.getValue().toString();
                System.out.println(f);
                if((A.length() != 0) && (B.length() != 0) && (f != "")){
                    int a = Integer.parseInt(A);
                    int b = Integer.parseInt(B);
                    int c = (int)f.charAt(0) - 48;
                    func = new Function(a, b, c);
                    func.countIntegral();
                    double score = func.getScore();
                    textAns.setText(String.valueOf(score));
                    button.setDisable(false);
                }
            }
        });;
    }


    public static void main(String[] args) {
        launch(args);
    }
}
