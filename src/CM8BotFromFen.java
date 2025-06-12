import java.util.Scanner;

public class CM8BotFromFen {
    public static void main(String[] args) {
        JNI jni = new JNI();
        Scanner scanner = new Scanner(System.in);
    System.out.println("You will play as white, and the bot will play as black.");
        System.out.println("You can enter a FEN string to start the game, but please ensure that you have made your first move as white.");
        System.out.println("Enter FEN string :");
        String fen = scanner.nextLine();

        // Call JNI bot to get best move int from FEN
        int moveInt = jni.playBestFromFen(fen);
        System.out.println("Raw best move int: " + moveInt);

        // Decode move into human-readable format
        String moveReadable = MoveDecoder.decodeMove(moveInt);
        System.out.println("Bot move: " + moveReadable);

        // Apply the move to the original FEN string
        String newFen = FenUpdater.applyMoveToFen(fen, moveReadable);
        System.out.println("New FEN after bot move:");
        System.out.println(newFen);
    }
}
