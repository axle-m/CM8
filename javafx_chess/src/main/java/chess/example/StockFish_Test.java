// KEEP THIS TEST FILE HERE WE NEED 
// IN CASE WE WANT TO MAKE 
// ANY FUTURE CHANGES 


package chess.example;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.Scanner;

import com.fasterxml.jackson.databind.DeserializationFeature;
import com.fasterxml.jackson.databind.ObjectMapper;

public class StockFish_Test {
    private static final String apiBase = "https://stockfish.online/api/s/v2.php";

    private static StockFish_API proccessPosition(String fen, int depth) throws Exception {
        for(int i = fen.length()-1; i >= 0; i--){
            if(fen.charAt(i) == '/'){
                fen = fen.substring(0, i) + "%2F" + fen.substring(i+1);
            }
            else if(fen.charAt(i) == ' '){
                fen = fen.substring(0, i) + "%20" + fen.substring(i+1);
            }
        }
        URI targetURI = new URI(String.format("%s?fen=%s&depth=%d", apiBase, fen, depth));
        HttpRequest httpRequest = HttpRequest.newBuilder()
             .uri(targetURI)
             .GET()
             .setHeader("Content-Type", "application/json")
             .build();
        
        HttpClient httpClient = HttpClient.newHttpClient();
        HttpResponse<String> response = httpClient.send(httpRequest, HttpResponse.BodyHandlers.ofString());

        ObjectMapper objectMapper = new ObjectMapper();

        StockFish_API eval = objectMapper.readValue(response.body(), StockFish_API.class);

        return eval;
    }

    public static void main(String[] args) throws Exception {
        String fen;
        int depth;
        Scanner in = new Scanner(System.in);
        System.out.println("Enter a Fen and a depth");
        fen = in.nextLine();
        depth = in.nextInt();
        System.out.println(proccessPosition(fen, depth));
    }
}
