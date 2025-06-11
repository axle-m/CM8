public class JNI {
    public native int makePlayerMove(String move, int promotion);
    public native int getBestMove(int depth);
    public native int playBestMove();
    public native int playBestFromFen(String fen);
    static {
        System.loadLibrary("chess"); // load your JNI C library
    }
}
