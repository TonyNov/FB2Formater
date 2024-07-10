package ru.tonynov.multitool;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.regex.Pattern;

public class FB2Formater {
    private FB2Formater() {

    }

    private static String loadFile(String path) {
        StringBuilder contentBuilder = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new FileReader(path, StandardCharsets.UTF_8))) {
            String line;
            while ((line = reader.readLine()) != null)
                contentBuilder.append(line).append(System.lineSeparator());
        } catch (Exception e) {
            System.out.println("Ошибка при чтении файла: " + e.getMessage());
        }
        return contentBuilder.toString();
    }

    private static String changeShablon(String fileData) {
        var shablon = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<FictionBook xmlns=\"http://www.gribuser.ru/xml/fictionbook/2.0\" xmlns:l=\"http://www.w3.org/1999/xlink\">\n <description>\n  <title-info>\n    <genre>fanfiction</genre>\n    <author>\n     <first-name>firstname</first-name>\n     <middle-name>middlename</middle-name>\n     <last-name>lastname</last-name>\n    </author>\n    <book-title>booktitle</book-title>\n    <annotation>\nannotationtext\n    </annotation>\n    <date></date>\n    <lang>ru</lang>\n    <sequence name = \"Новое\" />\n  </title-info>\n  <document-info>\n    <author>\n     <first-name>firstname</first-name>\n     <middle-name>middlename</middle-name>\n     <last-name>lastname</last-name>\n    </author>\n    <program-used>FictionBook Editor Release 2.6.7</program-used>\n    <date value=\"2022-10-29\">29 October 2022</date>\n    <id>0C7970A8-2B5C-4451-A983-7F06028C7101</id>\n    <version>1.0</version>\n    <history>\n     <p>1.0 — создание файла</p>\n    </history>\n  </document-info>\n </description>\n <body>\n  <title>\n   <p>firstname middlename lastname</p>\n   <p>booktitle</p>\n  </title>\n";
        var matcher = Pattern.compile("(?s)<first-name>(.*?)</first-name>").matcher(fileData);
        if (matcher.find()) {
            System.out.println("Имя: " + matcher.group(1));
            shablon = shablon.replace("firstname", matcher.group(1));
        } else {
            System.out.println("Имя: ");
            shablon = shablon.replace("firstname", "");
        }
        matcher = Pattern.compile("(?s)<last-name>(.*?)</last-name>").matcher(fileData);
        if (matcher.find()) {
            System.out.println("Фамилия: " + matcher.group(1));
            shablon = shablon.replace("lastname", matcher.group(1));
        } else {
            System.out.println("Фамилия: ");
            shablon = shablon.replace("lastname", "");
        }
        matcher = Pattern.compile("(?s)<middle-name>(.*?)</middle-name>").matcher(fileData);
        if (matcher.find()) {
            System.out.println("Отчество: " + matcher.group(1));
            shablon = shablon.replace("middlename", matcher.group(1));
        } else {
            System.out.println("Отчество: ");
            shablon = shablon.replace("middlename", "");
        }
        matcher = Pattern.compile("(?s)<annotation>(.*?)</annotation>").matcher(fileData);
        if (matcher.find())
            shablon = shablon.replace("annotationtext", matcher.group(1));
        else
            System.out.println("Аннотация не найдена!");
        matcher = Pattern.compile("(?s)<book-title>(.*?)</book-title>").matcher(fileData);
        if (matcher.find()) {
            System.out.println("Название книги: " + matcher.group(1));
            shablon = shablon.replace("booktitle", matcher.group(1));
        } else {
            System.out.println("Название книги: ");
            shablon = shablon.replace("booktitle", "");
        }
        return shablon;
    }

    public static void transormFB2(String filePath, boolean changeCurFile) {
        var fileData = loadFile(filePath);
        fileData = fileData.replace("<image xlink:href=\"#ficbook_logo.png\"/>", "");
        fileData = fileData.replace("xlink:href", "l:href");
        fileData = Pattern.compile("(?s)<binary(.*?)</binary>").matcher(fileData).replaceFirst("");
        var bookInfo = changeShablon(fileData);
        fileData = fileData.replace("</emphasis>", "");
        fileData = fileData.replace("<emphasis>", "");
        fileData = fileData.replace("<strong>", "");
        fileData = fileData.replace("</strong>", "");
        fileData = Pattern.compile("(?s)(.*?)<section>").matcher(fileData).replaceFirst("<section>");
        fileData = bookInfo + fileData;
        if (changeCurFile) {
            try (FileWriter writer = new FileWriter(filePath, StandardCharsets.UTF_8)) {
                writer.write(fileData);
            } catch (IOException e) {
                System.err.println("Ошибка при записи в файл: " + e.getMessage());
            }
        } else {
            Path path = Paths.get(filePath);
            try (FileWriter writer = new FileWriter(
                    path.getParent().resolve("(" + path.getFileName().toString()).toString(), StandardCharsets.UTF_8)) {
                writer.write(fileData);
            } catch (IOException e) {
                System.err.println("Ошибка при записи в файл: " + e.getMessage());
            }
        }
    }
}