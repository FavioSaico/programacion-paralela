package com.ejemplo;

import akka.actor.AbstractActor;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import java.io.File;
import java.io.IOException;
import akka.actor.Props;

public class ImageReaderActor extends AbstractActor {

    @Override
    public Receive createReceive() {
        return receiveBuilder()
                .match(String.class, this::readImage)
                .build();
    }

    private void readImage(String filePath) {
        try {
            BufferedImage image = ImageIO.read(new File(filePath));
            getSender().tell(image, getSelf());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static Props props() {
        return Props.create(ImageReaderActor.class);
    }
}
