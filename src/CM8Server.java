import java.net.*;
import java.io.*;

public class CM8Server {
    public static void main(String[] args) throws Exception {
        ServerSocket server = new ServerSocket(8000);
        JNI jni = new JNI();
        System.out.println("Server listening on port 8000...");

        while (true) {
            Socket client = server.accept();
            BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));

            String fen = in.readLine();
            String moveStr = in.readLine(); // optional: may be null

            String newFen = "";
            String move = "";

            if (moveStr != null && moveStr.length() > 0) {
                int result = jni.makePlayerMove(moveStr, 0, fen);
                newFen = FenUpdater.applyMoveToFen(fen, moveStr);
                int botMove = jni.playBestFromFen(newFen);
                move = MoveDecoder.decodeMove(botMove);
                newFen = FenUpdater.applyMoveToFen(newFen, move);
            } else {
                int botMove = jni.playBestFromFen(fen);
                move = MoveDecoder.decodeMove(botMove);
                newFen = FenUpdater.applyMoveToFen(fen, move);
            }

            out.write(move + "|" + newFen + "\n");
            out.flush();
            client.close();
        }
    }
}
