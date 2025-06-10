package chess.example;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.scene.image.Image;

import java.io.FileInputStream;

public class Challege extends Application {
    private static final int SIZE = 8;
    private ChessSquare[][] squares = new ChessSquare[SIZE][SIZE];
    private String[][] board = new String[SIZE][SIZE]; // piece codes like "wp", "bk", etc.
    private int selectedRow = -1, selectedCol = -1;

    @Override
    public void start(Stage primaryStage) throws Exception {
        GridPane grid = new GridPane();

        // Example: Set up a few pieces for demo. Expand to full setup as needed.
        board[1][4] = "bp"; // black pawn
        board[6][4] = "wp"; // white pawn
        board[0][3] = "bq"; // black queen
        board[7][3] = "wq"; // white queen

        for (int row = 0; row < SIZE; row++) {
            for (int col = 0; col < SIZE; col++) {
                String pos = "" + (char)('a' + col) + (8 - row);
                String piece = board[row][col];
                Image img = null;
                if (piece != null) {
                    img = new Image(new FileInputStream("assests/" + piece + ".png"));
                }
                ChessSquare square = new ChessSquare(pos, piece, img);
                square.setPrefSize(60, 60);
                square.setStyle("-fx-background-color: " + ((row + col) % 2 == 0 ? "#f0d9b5" : "#b58863") + ";");
                int r = row, c = col;
                square.setOnAction(e -> handleClick(r, c));
                squares[row][col] = square;
                grid.add(square, col, row);
            }
        }

        Scene scene = new Scene(grid, 480, 480);
        primaryStage.setTitle("Chess GUI");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void handleClick(int row, int col) {
        ChessSquare clicked = squares[row][col];
        if (selectedRow == -1 && clicked.getPiece() != null) {
            // Select a piece
            selectedRow = row;
            selectedCol = col;
            clicked.setStyle(clicked.getStyle() + "-fx-border-color: red; -fx-border-width: 3;");
        } else if (selectedRow != -1) {
            // Attempt move
            if (selectedRow != row || selectedCol != col) {
                // Move the piece
                String movingPiece = board[selectedRow][selectedCol];
                board[row][col] = movingPiece;
                board[selectedRow][selectedCol] = null;
                updateSquare(row, col, movingPiece);
                updateSquare(selectedRow, selectedCol, null);
                System.out.println("Moved " + movingPiece + " from " + squares[selectedRow][selectedCol].getPosition() + " to " + squares[row][col].getPosition());
            }
            // Reset selection
            squares[selectedRow][selectedCol].setStyle("-fx-background-color: " + ((selectedRow + selectedCol) % 2 == 0 ? "#f0d9b5" : "#b58863") + ";");
            selectedRow = selectedCol = -1;
        }
    }

    private void updateSquare(int row, int col, String piece) {
        board[row][col] = piece;
        Image img = null;
        if (piece != null) {
            try {
                img = new Image(new FileInputStream("assests/" + piece + ".png"));
            } catch (Exception e) {
                img = null;
            }
        }
        squares[row][col].setPiece(piece, img);
    }

    public static void main(String[] args) {
        launch(args);
    }
}