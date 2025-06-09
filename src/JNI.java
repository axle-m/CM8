public class JNI {
    public native int makePlayerMove(String move);
    public native int getBestMove();

    static {
        System.loadLibrary("yourNativeLibName"); // load your JNI C library
    }
}
