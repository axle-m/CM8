public class JNI {

    // Load the shared C library (e.g., attack.dll or libattack.so)
    static {
        System.loadLibrary("chess"); // Leave off "lib" and file extension
    }

    // Declare the native methods you want to call
    public static native void initAttackTables();
    public static native long getBishopAttacks(int square, long occupancy);
    public static native long getRookAttacks(int square, long occupancy);

    // Optional: Test call
    public static void main(String[] args) {
        initAttackTables();

        int square = 36; // e4
        long occupancy = 0x0000001008000000L;

        long bishop = getBishopAttacks(square, occupancy);
        long rook = getRookAttacks(square, occupancy);

        System.out.printf("Bishop attacks: 0x%016X\n", bishop);
        System.out.printf("Rook attacks:   0x%016X\n", rook);
    }
    public static native int squareToPos(String square);

}
