package com.ejemplo;

import akka.actor.AbstractActor;
import java.awt.image.BufferedImage;
import java.awt.Color;
import javax.imageio.ImageIO;
import java.io.File;
import java.io.IOException;
import akka.actor.Props;

public class ImageProcessingActor extends AbstractActor {

    @Override
    public Receive createReceive() {
        return receiveBuilder()
                .match(BufferedImage.class, this::processImage)
                .build();
    }

    private void processImage(BufferedImage image) {
        int width = image.getWidth();
        int height = image.getHeight();

        // Procesamiento de escala de grises
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                Color color = new Color(image.getRGB(x, y));
                int red = color.getRed();
                int green = color.getGreen();
                int blue = color.getBlue();
                int gray = (red + green + blue) / 3;
                Color newColor = new Color(gray, gray, gray);
                image.setRGB(x, y, newColor.getRGB());
            }
        }

        // Guarda la imagen procesada en el disco
        try {
            File outputImageFile = new File("src/main/resources/imagen_procesada.jpg");
            ImageIO.write(image, "jpg", outputImageFile);
            System.out.println("Imagen procesada guardada en: " + outputImageFile.getAbsolutePath());
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Envía la imagen procesada a otro actor o realiza acciones adicionales según tus necesidades.
        getSender().tell(image, getSelf());
    }
}
