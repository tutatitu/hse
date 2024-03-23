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
        return "Age: " + age;
    }

    public String Parse() {
        return getInitials() + '\n' + getSex() + '\n' + getAge();
    }
}
