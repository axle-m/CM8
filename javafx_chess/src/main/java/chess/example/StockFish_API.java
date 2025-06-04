package chess.example;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

@JsonIgnoreProperties(ignoreUnknown = true)
public class StockFish_API {
    private boolean success;
    private double evaluation;
    private int mate;
    private String bestmove;
    private String continuation;

    public boolean getSuccess() {
        return success;
    }
    public void setSuccess(boolean success) {
        this.success = success;
    }
    public double getEvaluation() {
        return evaluation;
    }
    public void setEvaluation(double evaluation) {
        this.evaluation = evaluation;
    }
    public int getMate() {
        return mate;
    }
    public void setMate(int mate) {
        this.mate = mate;
    }
    public String getBestmove() {
        return bestmove;
    }
    public void setBestmove(String bestmove) {
        this.bestmove = bestmove;
    }
    public String getContinuation() {
        return continuation;
    }
    public void setContinuation(String continuation) {
        this.continuation = continuation;
    }

    public String toString() {
        if(mate == 0){
            return "Test: " + evaluation;
        }
        return "Test: " + mate;
    }
}