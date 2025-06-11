public class TestJNI {
    public static void main(String[] args) {
        JNI jni = new JNI();

        int result = jni.getBestMove(5);
        System.out.println("Best move returned: " + result);

        int result1 = jni.playBestMove();
        System.out.println("Best move result: " + result1);

        String fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; // example FEN
        int result2 = jni.playBestFromFen(fen);
        System.out.println("Best move from FEN result: " + result2);

        int moveResult = jni.makePlayerMove("Pe2e4", 0);
        System.out.println("Player move result: " + moveResult);

        int exampleMove = 2099378;  
        int flag = 0;               

        int resultz = jni.makeMove(exampleMove, flag);
        System.out.println("makeMove result: " + resultz);
    }
}
