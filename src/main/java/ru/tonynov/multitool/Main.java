package ru.tonynov.multitool;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;

import java.awt.*;
import java.io.File;
import java.io.IOException;

public class Main extends JFrame {
    private JButton zipSomeFiles;
    private JPanel panel1;
    private JButton buttonFB21;
    private JButton buttonFB22;
    private JLabel label1;

    public static void replaceAll(String str, String from, String to) {
        int startPos = 0;
        while ((startPos = str.indexOf(from, startPos)) != -1) {
            str = str.substring(0, startPos) + to + str.substring(startPos + from.length());
            startPos += to.length();
        }
    }

    public static void eraseAllSubStr(String mainStr, String toErase) {
        int pos = mainStr.indexOf(toErase);
        while (pos != -1) {
            mainStr = mainStr.substring(0, pos) + mainStr.substring(pos + toErase.length());
            pos = mainStr.indexOf(toErase);
        }
    }

    private void archiver() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setMultiSelectionEnabled(true);
        fileChooser.setFileFilter(new FileNameExtensionFilter("Разные файлы", "txt", "png", "class"));
        int returnValue = fileChooser.showOpenDialog(null);
        if (returnValue == JFileChooser.APPROVE_OPTION) {
            File[] selectedFiles = fileChooser.getSelectedFiles();
            for (File file : selectedFiles) {
                try {
                    ZipUtil.zipFile(file.getPath(), ZipUtil.getFileNameWithoutExtension(file.getPath()) + ".zip");
                } catch (ZipCreationException cause) {
                    cause.printStackTrace();
                    break;
                }
                System.out.println("Архивирован файл: " + file.getPath());
            }
            System.out.println("\033[32mАрхивация завершена\033[0m");
        }
    }

    private void formaterFB2(boolean changeCurFile) {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setMultiSelectionEnabled(true);
        fileChooser.setFileFilter(new FileNameExtensionFilter("Книги", "fb2"));
        int returnValue = fileChooser.showOpenDialog(null);
        if (returnValue == JFileChooser.APPROVE_OPTION) {
            File[] selectedFiles = fileChooser.getSelectedFiles();
            var startTime = System.nanoTime();
            for (File file : selectedFiles) {
                try {
                    FB2Formater.transormFB2(file.getPath(), changeCurFile);
                } catch (Exception cause) {
                    System.out.println("Ошибка чтения");
                }
            }
            var endTime = System.nanoTime();
            var duration = (endTime - startTime);
            setTitle(String.valueOf(duration));
            System.out.println("Преобразование завершено");
        }
    }

    public Main() {
        setSize(400, 180);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setTitle("Multitool");
        setMinimumSize(getSize());
        setLayout(new BorderLayout());
        try {
            setIconImage(ImageIO.read(getClass().getResource("/icons8-круги-50.png")));
        } catch (IOException e) {
            e.printStackTrace();
        }
        panel1 = new JPanel();
        label1 = new JLabel("Расположение" + Main.class.getProtectionDomain().getCodeSource().getLocation().getPath());
        label1.setBackground(Color.white);
        label1.setForeground(Color.BLACK);
        zipSomeFiles = new JButton("Архивировать файлы");
        zipSomeFiles.addActionListener(e -> archiver());
        buttonFB21 = new JButton("Исправить FB2 c заменой");
        buttonFB21.addActionListener(e -> formaterFB2(true));
        buttonFB22 = new JButton("Исправить FB2 без замены");
        buttonFB22.addActionListener(e -> formaterFB2(false));
        panel1.add(label1, BorderLayout.WEST);
        panel1.add(zipSomeFiles, BorderLayout.WEST);
        panel1.add(buttonFB21, BorderLayout.WEST);
        panel1.add(buttonFB22, BorderLayout.WEST);
        add(panel1, BorderLayout.CENTER);
        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(Main::new);
    }
}