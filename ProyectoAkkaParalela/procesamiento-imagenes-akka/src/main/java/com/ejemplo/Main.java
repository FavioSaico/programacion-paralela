package com.ejemplo;

import akka.actor.ActorRef;
import akka.actor.ActorSystem;
import akka.actor.Props;

public class Main {
    public static void main(String[] args) {
        // Crea el sistema de actores
        ActorSystem system = ActorSystem.create("ImageProcessingSystem");

        // Crea los actores
       // Crea los actores
ActorRef imageReaderActor = system.actorOf(Props.create(ImageReaderActor.class), "imageReader");
ActorRef imageProcessingActor = system.actorOf(Props.create(ImageProcessingActor.class), "imageProcessing");

        // Envía la ruta de la imagen al actor de lectura
        String imagePath = "src/main/resources/imagen.jpg";
        imageReaderActor.tell(imagePath, imageProcessingActor);

        // Espera un tiempo para que los actores procesen la imagen (en un sistema real, deberías manejar mejor esto)
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Detiene el sistema de actores
        system.terminate();
    }
}
