public class ChessBot {
    // Load the DLL (no .dll extension needed)
    static {
        System.loadLibrary("chess"); 
    }

    // Declare native methods (must match C functions)
    public native int square(int x);               // Test function
    public native long getPawnAttacks(boolean isWhite, int square); // Chess function

    public static void main(String[] args) {
        ChessBot bot = new ChessBot();
        
        // Test 1: Simple JNI call
        System.out.println("Square of 5: " + bot.square(5));
        
        // Test 2: Chess logic call
        long attacks = bot.getPawnAttacks(true, 20); // White pawn at square 20
        System.out.println("Pawn attacks: " + attacks);
    }
}