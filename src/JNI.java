public class JNI {
    public native int makePlayerMove(String move, int promotion);
    public native int getBestMove();

    static {
        System.loadLibrary("chess"); // load your JNI C library
    }
}
