import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.time.format.ResolverStyle;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Input Full Name > ");
        String[] fullName = scanner.nextLine().split(" ");

        if (fullName.length != 3) {
            System.out.println("Error: Incorrect Full Name format");
            return;
        }
        for (String s : fullName) {
            if (!s.matches("[а-яА-Я]+")) {
                System.out.println("Error: Characters only");
                return;
            }
        }

        System.out.print("Input birth date in format dd.mm.yyyy > ");
        String date = scanner.nextLine();
        LocalDate birthday;

        try {
            birthday = LocalDate.parse(date, DateTimeFormatter.ofPattern("dd.MM.uuuu").withResolverStyle(ResolverStyle.STRICT));
        } catch (DateTimeParseException e) {
            System.out.println("Error: Incorrect date format or date doesn't exist");
            return;
        }

        System.out.println(new Person(fullName, birthday).Parse());
    }
}
