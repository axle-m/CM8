public class testFile {
    public native long maskBishopAttacks(int pos);

    static {
        System.loadLibrary("chessbridge"); 
    }

    public static void main(String[] args) {
        try{
        testFile t = new testFile();
        long result = t.maskBishopAttacks(28); // from what i understand e4 is square 28
        System.out.println("Bitboard result: " + result);
        } catch (UnsatisfiedLinkError e) {
            System.out.println("Native code library failed to load.\n" + e);
        }
        }
    }
}
