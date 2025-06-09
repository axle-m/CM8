import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.SocketException;
import java.util.List;

public class ServerSocketListener  implements Runnable {
    private Socket socket;
    private ClientConnectionData client;
    private List<ClientConnectionData> clientList;

    public ServerSocketListener(Socket s, List<ClientConnectionData> clientList) {
        socket = s;
        this.clientList = clientList;
    }

    private void setup() throws IOException{
        ObjectOutputStream socketOut = new ObjectOutputStream(socket.getOutputStream());
        ObjectInputStream socketIn = new ObjectInputStream(socket.getInputStream());
        String name = socket.getInetAddress().getHostName();

        client = new ClientConnectionData(socket, socketIn, socketOut, name);
        clientList.add(client);

        System.out.println("added client " + name);
    }
    
    private void processMoveMessage(MessageCtoS_move m){
        
    }

    @Override
    public void run() {
        try {
            setup();
            ObjectInputStream in = client.getInput();

            MessageCtoS_join joinMessage = (MessageCtoS_join) in.readObject();
            client.setUserName(joinMessage.userName);
            while(true){
                Message msg = (Message) in.readObject();
                if(msg instanceof MessageCtoS_move move){
                    processMoveMessage(move);
                }
                else if(msg instanceof MessageCtoS_Exit){
                    break;
                }
            }

        } catch (Exception ex) {
            if (ex instanceof SocketException) {
                System.out.println("Caught socket ex for " + 
                    client.getName());
            } else {
                System.out.println(ex);
                ex.printStackTrace();
            }
        } finally {
            clientList.remove(client); 

            try {
                client.getSocket().close();
            } catch (IOException ex) {}
        }
    }
        
}
