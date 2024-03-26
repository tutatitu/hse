import java.time.LocalDate;
import java.time.Period;

public class Person {
    private final String name, surname, patronymic;
    private final LocalDate birthday;

    public Person(String[] fullName, LocalDate birthday) {
        name = fullName[1];
        surname = fullName[0];
        patronymic = fullName[2];
        this.birthday = birthday;
    }

    private String getInitials() {
        return "Initials: " + surname + ' ' + name.charAt(0) + '.' + patronymic.charAt(0) + '.';
    }

    private String getSex() {
        if (patronymic.charAt(patronymic.length() - 1) == 'ч') {
            return "Sex: Male";
        } else {
            return "Sex: Female";
        }
    }

    private String getAge() {
        int age = Period.between(birthday, LocalDate.now()).getYears();
        if (age % 10 == 1 && age != 11)
            return "Age: " + age + " год";
        else if ((age % 10 == 2 || age % 10 == 3 || age % 10 == 4) && (age < 10 || age > 20))
            return "Age: " + age + " года";
        return "Age: " + age + " лет";
    }

    public String Parse() {
        return getInitials() + '\n' + getSex() + '\n' + getAge();
    }
}
