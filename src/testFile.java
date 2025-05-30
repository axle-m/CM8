public class testFile {

    public native long getKnightAttacks(int pos);

    static {
        System.loadLibrary("chessbridge"); 
    }

    public static void main(String[] args) {
        testFile test = new testFile();
        int position = 28; // e4
        long result = test.getKnightAttacks(position);
        System.out.println("Knight attack bitboard: " + result);
    }
}
