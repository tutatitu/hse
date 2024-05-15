import java.util.LinkedList;
import java.util.Queue;

public class Floor {
    private int approachingElevator = -1;
    public final Queue<ElevatorEvent> queue = new LinkedList<>();

    Floor() {
    }

    public synchronized boolean tryToStakeOutFloor(int elevatorId) {
        if (this.approachingElevator == -1 && !queue.isEmpty()) {
            this.approachingElevator = elevatorId;
            return true;
        }
        return false;
    }

    public synchronized void setApproachingElevator(int approachingElevator) {
        this.approachingElevator = approachingElevator;
    }

    public int getFloorQueueSize() {
        return queue.size();
    }
}