import java.util.*;

public class Elevator implements Runnable {
    private static int counter = 0;
    private final int id, capacity;
    private int currentFloor = 0, passengers = 0;

    private enum Direction {
        NONE, UP, DOWN
    }

    private Direction direction = Direction.NONE;

    private final House house;

    private final PriorityQueue<ElevatorEvent> tasks;

    public Elevator(int capacity, House house) {
        this.id = counter++;
        this.capacity = capacity;
        this.tasks = new PriorityQueue<>((event1, event2) ->
                Math.abs(currentFloor - event1.getDestination()) - Math.abs(currentFloor - event2.getDestination()));
        this.house = house;
    }

    public int getCurrentFloor() {
        return currentFloor;
    }

    public int getPassengers() {
        return passengers;
    }

    private void sleep() {
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public void moveElevator(int to) {
        if (to < currentFloor) {
            direction = Direction.DOWN;
        } else if (to > currentFloor) {
            direction = Direction.UP;
        }
        if (direction == Direction.UP) {
            while (currentFloor != to) {
                sleep();
                ++currentFloor;
                processFloor();
            }
        } else if (direction == Direction.DOWN) {
            while (currentFloor != to) {
                sleep();
                --currentFloor;
                processFloor();
            }
        }
        direction = Direction.NONE;
    }

    private void processFloor() {
        if (passengers != capacity) {
            if (house.getFloor(currentFloor).tryToStakeOutFloor(this.id)) {
                Queue<ElevatorEvent> queue = house.getFloor(currentFloor).queue;
                for (ElevatorEvent i : queue) {
                    if ((i.getDirection() == ElevatorEvent.Directions.UP && direction == Direction.UP)
                            || (i.getDirection() == ElevatorEvent.Directions.DOWN && direction == Direction.DOWN)) {
                        this.tasks.add(i);
                        i.setDirection(null);
                        ++passengers;
                        if (passengers == capacity) {
                            break;
                        }
                    }
                }
                queue.removeIf(value ->
                        value.getDirection() == null);
                house.getFloor(currentFloor).setApproachingElevator(-1);
            }
        }
    }

    public void run() {
        while (!Thread.interrupted()) {
            if (tasks.isEmpty()) {
                int pickUpFloor = -1;
                {
                    int i = currentFloor;
                    do {
                        if (house.getFloor(i).tryToStakeOutFloor(this.id)) {
                            pickUpFloor = i;
                            break;
                        }
                        ++i;
                        i %= house.getNumberOfFloors();
                    } while (i != currentFloor);
                }
                if (pickUpFloor == -1) {
                    continue;
                }
                moveElevator(pickUpFloor);
                while (passengers != capacity && !house.getFloor(pickUpFloor).queue.isEmpty()) {
                    this.tasks.add(house.getFloor(pickUpFloor).queue.poll());
                    ++passengers;
                }
                house.getFloor(pickUpFloor).setApproachingElevator(-1);
            } else {
                int deliverFloor = tasks.peek().getDestination();
                while (!tasks.isEmpty() && (deliverFloor = tasks.peek().getDestination()) == currentFloor) {
                    tasks.poll();
                    --passengers;
                }
                if (tasks.isEmpty()) {
                    continue;
                }
                moveElevator(deliverFloor);
                tasks.poll();
                --passengers;
            }
        }
    }
}