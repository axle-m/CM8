package chess.example;

import java.io.ObjectInputStream;
import java.util.Optional;

import javafx.application.Platform;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextInputDialog;

public class ChessGuiSocketListener implements Runnable {

    private ObjectInputStream socketIn;
    private ChessGuiClient chatGuiClient;
    private String username = null;

    // volatile guarantees that different threads reading the same variable will
    // always see the latest write.
    // volatile variables are not stored in caches.
    volatile boolean appRunning = false;

    public ChessGuiSocketListener(ObjectInputStream socketIn, ChessGuiClient chatClient) {
        this.socketIn = socketIn;
        this.chatGuiClient = chatClient;
    }

    private void processWelcomeMessage(MessageStoC_Welcome m) {
        String user = m.userName;

        if(this.username.equals(user)){
            Platform.runLater(() -> {
                chatGuiClient.getStage().setTitle("Chatter - " + username);
                chatGuiClient.getTextInput().setEditable(true);
                chatGuiClient.getSendButton().setDisable(false);
                chatGuiClient.getMessageArea().appendText("Welcome to the chat, " + username + "\n");
            });
        }
        else{
            Platform.runLater(() -> {
                chatGuiClient.getMessageArea().appendText(user + " joined the chat!\n");
            });
        }
    }

    private void processChatMessage(MessageStoC_Chat m) {
        //
        // TODO
        //
        Platform.runLater(() -> {
            chatGuiClient.getMessageArea().appendText(m.userName + ": " + m.msg + "\n");
        });
    }

    private void processExitMessage(MessageStoC_Exit m) {
        //
        // TODO
        //
        Platform.runLater(() -> {
            chatGuiClient.getMessageArea().appendText(m.userName + " has left the chat!\n");
        });
    }

 

    public void run() {
        try {
            appRunning = true;

            Platform.runLater(() -> {
                this.username = getName();
                chatGuiClient.sendMessage(new MessageCtoS_Join(username));
            });

            // If the user closes the UI window in ChatGuiClient, appRunning is changed to
            // false to exit this loop.
            while (appRunning) {
                Message msg = (Message) socketIn.readObject();

                if (msg instanceof MessageStoC_Welcome) {
                    processWelcomeMessage((MessageStoC_Welcome) msg);
                } 
                else if (msg instanceof MessageStoC_Chat) {
                    processChatMessage((MessageStoC_Chat) msg);
                } 
                else if (msg instanceof MessageStoC_Exit) {
                    processExitMessage((MessageStoC_Exit) msg);
                }
                else {
                    System.out.println("Unhandled message type: " + msg.getClass());
                }
            }
        } 
        catch (Exception ex) {
            System.out.println("Exception caught in listener - " + ex);
        } 
        finally {
            System.out.println("Client Listener exiting");
        }
    }

    private String getName() {
        String username = "";
        TextInputDialog nameDialog = new TextInputDialog();
        nameDialog.setTitle("Enter Chat Name");
        nameDialog.setHeaderText("Please enter your username.");
        nameDialog.setContentText("Name: ");

        while (username.equals("")) {
            Optional<String> name = nameDialog.showAndWait();
            if (!name.isPresent() || name.get().trim().equals(""))
                nameDialog.setHeaderText("You must enter a nonempty name: ");
            else
                username = name.get().trim();
        }
        return username;
    }

    public String getUserName(){
        return username;
    }
}
