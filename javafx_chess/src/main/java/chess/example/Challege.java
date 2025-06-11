package chess.example;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.scene.image.Image;

import java.io.FileInputStream;
import java.util.HashMap;

public class Challege extends Application {
    private ChessSquare[][] squares = new ChessSquare[8][8];
    private static String[][] board = new String[8][8];
    private int selectedRow = -1, selectedCol = -1;

    @Override
    public void start(Stage primaryStage) throws Exception {
        GridPane grid = new GridPane();

        board[0][0] = "br";
        board[0][1] = "bn";
        board[0][2] = "bb";
        board[0][3] = "bq";
        board[0][4] = "bk";
        board[0][5] = "bb";
        board[0][6] = "bn";
        board[0][7] = "br";

        board[7][0] = "wr";
        board[7][1] = "wn";
        board[7][2] = "wb";
        board[7][3] = "wq";
        board[7][4] = "wk";
        board[7][5] = "wb";
        board[7][6] = "wn";
        board[7][7] = "wr";

        for(int i = 0; i < 8; i++){
            board[1][i] = "bp";
            board[6][i] = "wp";
        }

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
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

        System.out.println(createFen());
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
                System.out.println(createFen());
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

    public static String createFen() {
        StringBuilder fen = new StringBuilder();
        HashMap<String, String> imageToFen = new HashMap<>();
        imageToFen.put("bb", "b");
        imageToFen.put("bk", "k");
        imageToFen.put("bn", "n");
        imageToFen.put("bp", "p");
        imageToFen.put("br", "r");
        imageToFen.put("bq", "q");
        imageToFen.put("wb", "B");
        imageToFen.put("wk", "K");
        imageToFen.put("wn", "N");
        imageToFen.put("wp", "P");
        imageToFen.put("wq", "Q");
        imageToFen.put("wr", "R");

        for (int i = 0; i < board.length; i++) {
            int space = 0;
            for (int j = 0; j < board[i].length; j++) {
                if (board[i][j] == null) {
                    space++;
                } 
                else {
                    if (space > 0) {
                        fen.append(space);
                        space = 0;
                    }
                    fen.append(imageToFen.get(board[i][j]));
                }
            }
            if (space > 0) {
                fen.append(space);
            }
            if (i < board.length - 1) {
                fen.append('/');
            }
        }
        return fen.toString();
    }

    public static void main(String[] args) {
        launch(args);
    }
}