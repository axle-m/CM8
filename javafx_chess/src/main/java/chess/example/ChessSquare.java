package chess.example;

import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

public class ChessSquare extends Button {
    private String position;
    private String piece;

    public ChessSquare(String position, String piece, Image image) {
        this.position = position;
        this.piece = piece;

        ImageView imageView = new ImageView(image);
        imageView.setFitWidth(60);
        imageView.setFitHeight(60);
        setGraphic(imageView);

        setOnAction(e -> {
            System.out.println("Clicked square: " + position);
            System.out.println("Piece: " + piece);
        });
    }

    public void setPiece(String newPiece, Image image) {
        this.piece = newPiece;
        setGraphic(new ImageView(image));
    }

    public String getPosition() { 
        return position; 
    }
    public String getPiece() { 
        return piece;
    }
}
