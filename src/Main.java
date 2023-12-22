import nativeLib.NativeLib;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);
        System.out.print("Введите символы для паролей: ");
        String characters = input.nextLine();
        System.out.println("");
        System.out.print("Введите длинну паролей: ");
        int length = input.nextInt();
        System.out.println("Генерируем пароли...");


        char[] charArray = characters.toCharArray();
        String[] symbols = new String[charArray.length];
        for (int i = 0; i < charArray.length; i++) {
            symbols[i] = String.valueOf(charArray[i]);
        }

        String password = "";
        NativeLib nativelib = new NativeLib();
        nativelib.generatePass(symbols, length, password);

        System.out.println("Все пароли сгенерированы!");
    }
}


//java -cp . -Djava.library.path="C:\mpp\Generator\src\nativeLib" Main.java