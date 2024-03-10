import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException, FileNotFoundException {
        Scanner scanner = new Scanner(System.in);
        HashMap<Character, Integer> map = new HashMap<>();

        System.out.print("Input FilePath > ");
        Path inputPath = Paths.get(scanner.next());
        if (Files.isDirectory(inputPath.toAbsolutePath()) || !Files.exists(inputPath.toAbsolutePath())) {
            throw new FileNotFoundException("File not found");
        }

        System.out.print("Output FilePath > ");
        Path outputPath = Paths.get(scanner.next());
        if (Files.isDirectory(outputPath.toAbsolutePath())) {
            throw new FileNotFoundException("Directory entered");
        }

        File in = new File(String.valueOf(inputPath.toAbsolutePath()));
        InputStream input = new FileInputStream(in);
        int size = input.available();

        for (int i = 0; i < size; ++i) {
            char temp = (char) input.read();
            if (Character.isLetter(temp)) {
                map.putIfAbsent(temp, 0);
                map.put(temp, map.get(temp) + 1);
            }
        }

        File out = new File(String.valueOf(outputPath.toAbsolutePath()));
        OutputStream output = new FileOutputStream(out);

        for (Character x : map.keySet()) {
            output.write((x + " - " + map.get(x) + '\n').getBytes(StandardCharsets.UTF_8));
        }

        input.close();
        output.close();
    }
}
