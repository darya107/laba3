import java.util.Scanner;
import java.io.*;
public class Main {
    final static Scanner scan = new Scanner(System.in);

    public static void main(String[] args) {
        int rows;
        int cols;
        int[][] matrix;
        String textInput;
        String textOutput;
        System.out.println("Упорядочить в порядке возрастания элементы строк данной матрицы, после чего упорядочить строки по убыванию последних элементов полученных строк. Используйте сортировку подсчётом.");
        textInput = "Как вы хотите ввести матрицу, через консоль или использовать файл ? (1 - консоль, 2 - файл)";
        if (selectWorkType(textInput) == 1) {
            System.out.println("Введите количество строк матрицы:");
            rows = enterN();
            System.out.println("Введите количество столбцов матрицы:");
            cols = enterN();
            matrix = enterMatrixInConsole(rows,cols);
            printMatrix(matrix);
        } else {
            matrix = readMatrixFile();
        }
        sort(matrix);
        textOutput = "Как вы хотите вывести результат, через консоль или использовать файл ? (1 - консоль, 2 - файл)";
        if (selectWorkType(textOutput) == 1) {
                System.out.println("Отсортированная матрица");
                printMatrix(matrix);
        }
        else {
            writeResultInFile(matrix);
        }
        scan.close();
    }

    public static int selectWorkType(String text) {
        int choice;
        boolean isInCorrect;
        choice = 1;
        System.out.println(text);
        do {
            isInCorrect = false;
            try {
                choice = Integer.parseInt(scan.nextLine());
            } catch (NumberFormatException e) {
                isInCorrect = true;
                System.out.println("Неправильно введены данные.Повторите ввод!");
            }
            if (!isInCorrect && (choice != 1) && (choice != 2)) {
                isInCorrect = true;
                System.out.println("Число не входит в диапазон");
            }
        } while (isInCorrect);
        return choice;

    }

    public static int enterN() {
        int n = 0;
        final int MIN_N = 0;
        final int MAX_N = 100;
        boolean isInCorrect;
        do {
            isInCorrect = false;
            try {
                n = Integer.parseInt(scan.nextLine());
            } catch (NumberFormatException e) {
                isInCorrect = true;
                System.out.println("Ошибка! Проверьте правильность ввода!!!: ");
            }
            if (!isInCorrect && (n > MAX_N) || (n < MIN_N)) {
                isInCorrect = true;
                System.out.println("Число не входит в диапазон!");
            }
        } while (isInCorrect);
        return n;
    }

    public static String inputFilePath(boolean isForRead) {
        String path;
        boolean isIncorrect;
        File Res;
        isIncorrect = true;
        do {
            if (isForRead) {
                System.out.println("Введите путь для файла для чтения");
            } else {
                System.out.println("Введите путь для файла для записи");
            }
            path = scan.nextLine();
            Res = new File(path);
            if (!path.endsWith(".txt"))
                System.out.println("Неправильное расширение файла.Повторите ввод :");
            else if (!Res.exists())
                System.out.println("Файл недоступен. Повторите ввод:");
            else if (!Res.canWrite())
                System.out.println("Программа не может записать в файл.попробуйте снова.");
            else
                isIncorrect = false;
        } while (isIncorrect);
        return path;
    }

    public static int[][] readMatrixFile() {
        int[][] matrix = null;
        boolean fileReadSuccessfully = false;
        while (!fileReadSuccessfully) {
            String pathToFile = inputFilePath(true);
            try (Scanner scanner = new Scanner(new FileInputStream(pathToFile))) {
                if (scanner.hasNextInt()) {
                    int rows = scanner.nextInt();
                    int cols = scanner.nextInt();
                    matrix = new int[rows][cols];
                    for (int i = 0; i < rows; i++) {
                        for (int j = 0; j < cols; j++) {
                            if (scanner.hasNextInt()) {
                                matrix[i][j] = scanner.nextInt();
                            } else {
                                throw new IOException(("Недостаточно данных в файле для заполнения матрицы"));
                            }
                        }
                    }
                    fileReadSuccessfully = true;
                } else {
                    System.out.println("Файл пуст или не содержит размер матрицы");
                }
            } catch (IOException exc) {
                System.out.println("Ошибка чтения файла:" + exc.getMessage() + "\nПопробуйте снова");
            }
        }
        return matrix;
    }

    public static int[][] enterMatrixInConsole(int rows,int cols) {
        int[][] matrix = new int[rows][];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
        }
        boolean isInCorrect;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                do {
                    isInCorrect = false;
                    System.out.println("Введите элемент матрицы Matrix[" + (i + 1) + "," + (j + 1) + "]:");
                    try {
                        (matrix[i][j]) = Integer.parseInt(scan.nextLine());
                    } catch (NumberFormatException e) {
                        isInCorrect = true;
                        System.out.println("Ошибка! Проверьте правильность ввода!!!: ");
                    }
                }
                while (isInCorrect);
            }
        }
        return matrix;
    }

    public static int findMax(int[] arr) {
        int max = arr[0];
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        return max;
    }

    public static int findMin(int[] arr) {
        int min = arr[0];
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] < min) {
                min = arr[i];
            }
        }
        return min;
    }
    public static void sortRow(int[] arr) {
        int max = findMax(arr);
        int min = findMin(arr);


        int[] counts = new int[max - min + 1];//все элементы нули

        for (int i = 0; i < arr.length; i++) {
            counts[arr[i] - min]++;
        }


        int currentIndex = 0;
        for (int val = 0; val < counts.length; val++) {
            int countValue = counts[val];
            for (int i = 0; i < countValue; i++) {
                arr[currentIndex++] = val + min;

            }

        }
    }
    public static void sortRowsLastElements(int[][] matrix) {
        for (int i = 1; i < matrix.length; i++) {
            for (int j = 0; j < matrix.length - i; j++) {
                if (matrix[j][matrix[i].length - 1] < matrix[j + 1][matrix[i].length - 1]) {
                    int[] temp = matrix[j];
                    matrix[j] = matrix[j + 1];
                    matrix[j + 1] = temp;
                }
            }
        }
    }


    public static void sort(int[][] matrix) {
        for (int i = 0; i < matrix.length; i++) {
            sortRow(matrix[i]);
        }
        sortRowsLastElements(matrix);
    }



    public static void printMatrix ( int[][] matrix){
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                System.out.print(matrix[i][j] + "  ");
            }
            System.out.println();
        }
    }

    public static void writeResultInFile (int[][] matrix){
        File Res = new File(inputFilePath(false));
        try (BufferedWriter pw = new BufferedWriter(new FileWriter(Res))) {
            pw.append("отсортированная матрица ");
            pw.append(System.lineSeparator());
            for (int i = 0; i < matrix.length; i++) {
                for (int j = 0; j < matrix[i].length; j++) {
                    pw.append(matrix[i][j] + " ");
                }
                pw.append(System.lineSeparator()); // Добавляем перенос строки после каждой строки матрицы
            }
        } catch (IOException e) {
            System.out.println("Ошибка записи ");
        }

        System.out.println("Ответ записан");
    }
}




