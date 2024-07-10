package ru.tonynov.multitool;

import java.io.IOException;

public class ZipCreationException extends IOException {
    public ZipCreationException(String message) {
        super(message);
    }

    public ZipCreationException(Throwable cause) {
        super(cause);
    }

    public ZipCreationException(String message, Throwable cause) {
        super(message, cause);
    }
}