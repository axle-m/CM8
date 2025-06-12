import java.util.*;

public class FenUpdater {

    private static final Map<Character, Integer> fileMap = Map.of(
        'a', 0, 'b', 1, 'c', 2, 'd', 3, 'e', 4, 'f', 5, 'g', 6, 'h', 7
    );

    private static final Map<Character, Character> promotionMap = Map.of(
        'q', 'q', 'r', 'r', 'b', 'b', 'n', 'n'
    );

    public static String applyMoveToFen(String fen, String moveDesc) {
        // Split FEN
        String[] fenParts = fen.split(" ");
        String board = fenParts[0];
        String turn = fenParts[1];
        String castling = fenParts[2];
        String enPassant = fenParts[3];
        int halfmoveClock = Integer.parseInt(fenParts[4]);
        int fullmoveNumber = Integer.parseInt(fenParts[5]);

        // Parse move like "Pc7 to c5 double push"
        String[] parts = moveDesc.split(" ");
        char piece = parts[0].charAt(0);
        String from = parts[1];
        String to = parts[3];

// Promotion detection: e.g. "c7 to c8=Q" or with "=" sign somewhere
char promotedPiece = ' ';
int eqIndex = moveDesc.indexOf('=');
if (eqIndex != -1 && eqIndex + 1 < moveDesc.length()) {
    promotedPiece = moveDesc.charAt(eqIndex + 1);
}
        // e.g., "c5"

        boolean isCapture = moveDesc.contains("captures");
        boolean isDoublePush = moveDesc.contains("double push");
        boolean isEnPassant = moveDesc.contains("en passant");
        boolean isCastle = moveDesc.contains("castle");

        if (moveDesc.contains("=")) {
            promotedPiece = moveDesc.charAt(moveDesc.indexOf('=') + 1);
        }

        // Convert board to 2D array
        char[][] boardArr = parseBoard(board);

        int fromRow = 8 - Character.getNumericValue(from.charAt(1));
        int fromCol = fileMap.get(from.charAt(0));
        int toRow = 8 - Character.getNumericValue(to.charAt(1));
        int toCol = fileMap.get(to.charAt(0));

        // Perform the move
        char movingPiece = boardArr[fromRow][fromCol];
        boardArr[fromRow][fromCol] = '.';

        if (promotedPiece != ' ') {
            movingPiece = Character.isUpperCase(movingPiece) ?
                          Character.toUpperCase(promotedPiece) :
                          Character.toLowerCase(promotedPiece);
        }

        boardArr[toRow][toCol] = movingPiece;

        // Update en passant target square
        enPassant = "-";
        if (Character.toLowerCase(movingPiece) == 'p' && isDoublePush) {
            int epRow = (fromRow + toRow) / 2;
            enPassant = "" + (char)('a' + fromCol) + (8 - epRow);
        }

        // Update halfmove clock
        if (Character.toLowerCase(movingPiece) == 'p' || isCapture) {
            halfmoveClock = 0;
        } else {
            halfmoveClock++;
        }

        // Update fullmove number
        if (turn.equals("b")) {
            fullmoveNumber++;
        }

        // Flip side to move
        turn = turn.equals("w") ? "b" : "w";

        // Convert back to FEN string
        String newBoard = boardToFen(boardArr);

        return String.format("%s %s %s %s %d %d",
            newBoard, turn, castling, enPassant, halfmoveClock, fullmoveNumber);
    }

    private static char[][] parseBoard(String fenBoard) {
        char[][] board = new char[8][8];
        String[] rows = fenBoard.split("/");

        for (int i = 0; i < 8; i++) {
            int col = 0;
            for (char c : rows[i].toCharArray()) {
                if (Character.isDigit(c)) {
                    int empty = Character.getNumericValue(c);
                    for (int j = 0; j < empty; j++) {
                        board[i][col++] = '.';
                    }
                } else {
                    board[i][col++] = c;
                }
            }
        }

        return board;
    }

    private static String boardToFen(char[][] board) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 8; i++) {
            int emptyCount = 0;
            for (int j = 0; j < 8; j++) {
                char c = board[i][j];
                if (c == '.') {
                    emptyCount++;
                } else {
                    if (emptyCount > 0) {
                        sb.append(emptyCount);
                        emptyCount = 0;
                    }
                    sb.append(c);
                }
            }
            if (emptyCount > 0) sb.append(emptyCount);
            if (i < 7) sb.append('/');
        }
        return sb.toString();
    }
}
