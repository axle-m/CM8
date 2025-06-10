package chess.example;

import java.io.FileInputStream;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.EventType;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;

public class Challege extends Application{
    private Stage stage;

    @Override
    public void start(Stage primaryStage) throws Exception {      
        FileInputStream inputstream = new FileInputStream("assests/bb.png");        
        Image image = new Image(inputstream);
        ImageView imageView = new ImageView(image); 

        this.stage = primaryStage;

        imageView.setX(100); 
        imageView.setY(200);
        
        //setting the fit height and width of the image view 
        imageView.setFitHeight(200); 
        imageView.setFitWidth(200); 
        
        //Setting the preserve ratio of the image view 
        imageView.setPreserveRatio(true);  
        
        //Creating a Group object  
        Group root = new Group(imageView);  
        
        //Creating a scene object 
        Scene scene = new Scene(root, 600, 500);  
        
        //Setting title to the Stage 
        primaryStage.setTitle("Loading an image");  
        
        //Adding scene to the stage 
        primaryStage.setScene(scene);
        
        //Displaying the contents of the stage 
        primaryStage.show(); 
    }
      public static void main(String args[]) { 
      launch(args); 
   } 
}