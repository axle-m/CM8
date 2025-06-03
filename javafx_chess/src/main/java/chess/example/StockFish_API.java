package chess.example;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import org.json.JSONObject;

public class StockFish_API {

    private String bestMove;
    private Double evaluation;
    private Integer mate;
    private String continuation;
    private Integer depth;

    public void getMoveFromFEN(String fen) {
        try {
            String urlString = "https://stockfish.online/api/s/v2.php?fen=" + fen.replace(" ", "%20");
            URL url = new URL(urlString);
            HttpURLConnection con = (HttpURLConnection) url.openConnection();

            con.setRequestMethod("GET");
            con.setRequestProperty("Accept", "application/json");

            BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
            String inputLine;
            StringBuilder responseBuilder = new StringBuilder();

            while ((inputLine = in.readLine()) != null) {
                responseBuilder.append(inputLine);
            }
            in.close();

            JSONObject responseJson = new JSONObject(responseBuilder.toString());

            if (responseJson.getBoolean("success")) {
                String bestmoveFull = responseJson.optString("bestmove", "");
                this.bestMove = bestmoveFull.replace("bestmove ", "").split(" ")[0];

                this.evaluation = responseJson.has("evaluation") ? responseJson.getDouble("evaluation") : null;
                this.mate = responseJson.isNull("mate") ? null : responseJson.getInt("mate");
                this.continuation = responseJson.optString("continuation", "");
                this.depth = responseJson.has("depth") ? responseJson.getInt("depth") : null;
            } else {
                System.out.println("Error: API returned unsuccessful result.");
            }

        } catch (Exception e) {
            System.err.println("Exception: " + e.getMessage());
        }
    }

    // Getters
    public String getBestMove() {
        return bestMove;
    }

    public Double getEvaluation() {
        return evaluation;
    }

    public Integer getMate() {
        return mate;
    }

    public String getContinuation() {
        return continuation;
    }

    public Integer getDepth() {
        return depth;
    }

    public void printInfo() {
        System.out.println("Best Move: " + bestMove);
        System.out.println("Evaluation: " + evaluation);
        System.out.println("Mate: " + mate);
        System.out.println("Continuation: " + continuation);
        System.out.println("Depth: " + depth);
    }

    // Main method for testing
    public static void main(String[] args) {
        String fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        StockFish_API stockfish = new StockFish_API();
        stockfish.getMoveFromFEN(fen);
        stockfish.printInfo();
    }
}
