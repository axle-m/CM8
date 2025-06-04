package sockets;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.SocketException;
import java.util.List;

public class ChessServerSocketListener  implements Runnable {
    private ChessClientConnectionData client;
    private List<ChessClientConnectionData> clientList;

    public ChessServerSocketListener(ChessClientConnectionData client, List<ChessClientConnectionData> clientList) {
        this.client = client;
        this.clientList = clientList;
    }

    private void processChatMessage(MessageCtoS_Chat m) {
        System.out.println("Chat received from " + client.getUserName() + " - broadcasting");
        broadcast(new MessageStoC_Chat(client.getUserName(), m.msg), null);
    }

    private void processListMessage(MessageCtoS_List m){
        System.out.println("List received from " + client.getUserName() + " - broadcasting");
        broadcast(new MessageStoC_List(clientList, client.getUserName()), null);
    }

    /**
     * Broadcasts a message to all clients connected to the server.
     */
    public void broadcast(Message m, ChessClientConnectionData skipClient) {
        try {
            System.out.println("broadcasting: " + m);
            for (ChessClientConnectionData c : clientList){
                // if c equals skipClient, then c.
                // or if c hasn't set a userName yet (still joining the server)
                if ((c != skipClient) && (c.getUserName()!= null)){
                    c.getOut().writeObject(m);
                }
            }
        } catch (Exception ex) {
            System.out.println("broadcast caught exception: " + ex);
            ex.printStackTrace();
        }        
    }

    public void broadcastOnly(Message m, ChessClientConnectionData onlyClient){
        try {
            System.out.println("broadcasting: " + m);
            for(ChessClientConnectionData c: clientList){
                if((c == onlyClient) && (c.getUserName() != null)){
                    c.getOut().writeObject(m);
                }
            }
        }
        catch(Exception ex){
            System.out.println("broadcast caught exception: " + ex);
            ex.printStackTrace();
        }
    }

    @Override
    public void run() {
        try {
            ObjectInputStream in = client.getInput();

            MessageCtoS_Join joinMessage = (MessageCtoS_Join)in.readObject();
            client.setUserName(joinMessage.userName);

            // Broadcast the welcome back to the client that joined. 
            // Their UI can decide what to do with the welcome message.
            broadcast(new MessageStoC_Welcome(joinMessage.userName), null);
            
            while (true) {
                Message msg = (Message) in.readObject();
                if (msg instanceof MessageCtoS_Quit) {
                    break;
                }
                else if (msg instanceof MessageCtoS_Chat) {
                    processChatMessage((MessageCtoS_Chat) msg);
                }
                else if(msg instanceof MessageCtoS_List){
                    processListMessage((MessageCtoS_List) msg);
                }
                else {
                    System.out.println("Unhandled message type: " + msg.getClass());
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
            //Remove client from clientList
            clientList.remove(client); 

            // Notify everyone that the user left.
            broadcast(new MessageStoC_Exit(client.getUserName()), client);

            try {
                client.getSocket().close();
            } catch (IOException ex) {}
        }
    }
}
