public class HouseLogger implements Runnable {
    private int maxWaiting = 0;
    private final House building;

    HouseLogger(final House building) {
        this.building = building;
    }

    public void run() {
        while (!Thread.interrupted()) {
            for (int i = building.getNumberOfFloors() - 1; i >= 0; --i) {
                System.out.print("Floor: " + i + " ");
                System.out.print("Wait: " + building.getFloor(i).getFloorQueueSize() + " ");
                maxWaiting = Math.max(building.getFloor(i).getFloorQueueSize(), maxWaiting);
                System.out.print("Here:");
                for (int j = 0; j < building.getNumberOfElevators(); ++j) {
                    if (building.getElevator(j).getCurrentFloor() == i) {
                        System.out.print(" " + j);
                    }
                }
                System.out.println();
            }
            for (int i = 0; i < building.getNumberOfElevators(); ++i) {
                System.out.print("Elevator: " + i + " ");
                System.out.print("Load: " + building.getElevator(i).getPassengers());
                System.out.println();
            }
            System.out.println("Max number of waiters was " + maxWaiting);
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
            System.out.print("\033[H\033[2J");
        }
        System.out.print("\033[H\033[2J");
    }
}