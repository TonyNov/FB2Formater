package ru.tonynov.multitool;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

public class ZipUtil {
    private ZipUtil() {

    }

    public static void zipFile(String sourceFilePath, String destinationZipPath) throws ZipCreationException {
        File sourceFile = new File(sourceFilePath);
        try (FileInputStream fis = new FileInputStream(sourceFile);
                FileOutputStream fos = new FileOutputStream(destinationZipPath);
                ZipOutputStream zos = new ZipOutputStream(fos)) {
            ZipEntry zipEntry = new ZipEntry(sourceFile.getName());
            zos.putNextEntry(zipEntry);
            byte[] buffer = new byte[1024];
            int length;
            while ((length = fis.read(buffer)) >= 0) {
                zos.write(buffer, 0, length);
            }
        } catch (Exception e) {
            throw new ZipCreationException("Ошибка при создании ZIP-архива", e);
        }
    }

    public static void archiveFilesInDirectory(String directoryPath) throws ZipCreationException {
        File directory = new File(directoryPath);
        if (!directory.exists())
            throw new ZipCreationException("Директория не найдена: " + directoryPath);
        for (File file : directory.listFiles()) {
            if (file.isFile()) {
                String fileNameWithoutExtension = getFileNameWithoutExtension(file.getName());
                String zipFileName = fileNameWithoutExtension + ".zip";
                zipFile(file.getAbsolutePath(), zipFileName);
            }
        }
    }

    public static String getFileNameWithoutExtension(String fileName) {
        int dotIndex = fileName.lastIndexOf('.');
        return fileName.substring(0, dotIndex);
    }
}
