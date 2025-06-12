public class JNI {
    public native int makePlayerMove(String move, int promotion, String fen);
    public native int getBestMove(int depth);
    public native int playBestMove();
    public native int playBestFromFen(String fen);
    public native int makeMove(int move, int flag);
    static {
        System.loadLibrary("chess"); // load your JNI C library
    }
}
