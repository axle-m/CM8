public class MoveDecoder {

    private static final String[] squareNames = {
        "a1","b1","c1","d1","e1","f1","g1","h1",
        "a2","b2","c2","d2","e2","f2","g2","h2",
        "a3","b3","c3","d3","e3","f3","g3","h3",
        "a4","b4","c4","d4","e4","f4","g4","h4",
        "a5","b5","c5","d5","e5","f5","g5","h5",
        "a6","b6","c6","d6","e6","f6","g6","h6",
        "a7","b7","c7","d7","e7","f7","g7","h7",
        "a8","b8","c8","d8","e8","f8","g8","h8"
    };

    private static final String[] pieceNames = {
        "P", "N", "B", "R", "Q", "K", "?", "?", "?", "?", "?"
    };

    private static final String[] promotedNames = {
        "", "Knight", "Bishop", "Rook", "Queen"
    };

    public static String decodeMove(int move) {
        int from = (move) & 0x3F;
        int to = (move >> 6) & 0x3F;
        int piece = (move >> 12) & 0xF;
        int promoted = (move >> 16) & 0xF;

        boolean isCapture = (move & 0x100000) != 0;
        boolean doublePush = (move & 0x200000) != 0;
        boolean enPassant = (move & 0x400000) != 0;
        boolean castle = (move & 0x800000) != 0;

        StringBuilder sb = new StringBuilder();
        sb.append(pieceNames[Math.min(piece, 5)]).append(" ");
        sb.append(squareNames[from]).append(" to ").append(squareNames[to]);

        if (promoted != 0) {
            sb.append(" (promotes to ").append(promotedNames[Math.min(promoted, 4)]).append(")");
        }

        if (isCapture) sb.append(" [capture]");
        if (doublePush) sb.append(" [double push]");
        if (enPassant) sb.append(" [en passant]");
        if (castle) sb.append(" [castle]");

        return sb.toString();
    }
}
