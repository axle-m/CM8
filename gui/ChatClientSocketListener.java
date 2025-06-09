import java.io.ObjectInputStream;

public class ChatClientSocketListener implements Runnable {
    private ObjectInputStream socketIn;

    public ChatClientSocketListener(ObjectInputStream socketIn) {
        this.socketIn = socketIn;
    }

    private static void processExitMessage(MessageStoC_Exit m){
        System.out.println(m);
    }

    private static void processMoveMessage(MessageStoC_move m){
        
    }


    @Override
    public void run() {
        try {
            while (true) {
                Message msg = (Message) socketIn.readObject();

                if(msg instanceof MessageStoC_move){
                    processMoveMessage((MessageStoC_move) msg);
                }
                else if(msg instanceof MessageStoC_Exit exitMsg){
                    processExitMessage(exitMsg);
                }
            }
        } catch (Exception ex) {
            System.out.println("Exception caught in listener - " + ex);
        } finally{
            System.out.println("Client Listener exiting");
        }
    }
}
