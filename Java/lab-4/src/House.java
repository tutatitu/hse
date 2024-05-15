import java.io.IOException;

public class House {
    private final int numberOfFloors, numberOfElevators;
    private final Floor[] floors;
    private final Elevator[] elevators;

    House(int numberOfFloors, int numberOfElevators, int elevatorCapacity) throws IOException {
        this.floors = new Floor[numberOfFloors];
        for (int i = 0; i < numberOfFloors; ++i) {
            this.floors[i] = new Floor();
        }
        this.numberOfFloors = numberOfFloors;

        this.elevators = new Elevator[numberOfElevators];
        for (int i = 0; i < numberOfElevators; ++i) {
            this.elevators[i] = new Elevator(elevatorCapacity, this);
        }
        this.numberOfElevators = numberOfElevators;

        Thread[] threads = new Thread[numberOfElevators];
        for (int i = 0; i < numberOfElevators; ++i) {
            threads[i] = new Thread(this.elevators[i]);
        }
        for (int i = 0; i < numberOfElevators; ++i) {
            threads[i].start();
        }

        HouseLogger buildingLogger = new HouseLogger(this);
        Thread loggerThread = new Thread(buildingLogger);
        loggerThread.start();

        PeopleGenerator peopleGenerator = new PeopleGenerator(this);
        Thread generatorThread = new Thread(peopleGenerator);
        generatorThread.start();
    }

    public int getNumberOfFloors() {
        return this.numberOfFloors;
    }

    public int getNumberOfElevators() {
        return this.numberOfElevators;
    }

    public synchronized Floor getFloor(int i) {
        return this.floors[i];
    }

    public Elevator getElevator(int i) {
        return this.elevators[i];
    }
}
