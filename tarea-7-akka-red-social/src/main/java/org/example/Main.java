package org.example;

import akka.actor.ActorSystem;
import akka.actor.ActorRef;
import akka.actor.Props;

public class Main {
    public static void main(String[] args) {

        // Crea el sistema de actores
        ActorSystem system = ActorSystem.create("CadenaActores");

        // Crea los actores en la cadena
        ActorRef actorD = system.actorOf(Props.create(User.class, "ActorD"));
        ActorRef actorC = system.actorOf(Props.create(User.class, "ActorC"));
        ActorRef actorB = system.actorOf(Props.create(User.class, "ActorB"));
        ActorRef actorA = system.actorOf(Props.create(User.class, "ActorA"));

        // ENVIAR MENSAJES
        MensajeCadena ms = new MensajeCadena("Hola como estas");
        actorA.tell(ms,actorB);

        // AGREGAR SEGUIDOR
        actorA.tell(new Follow(),actorB); // // actor B envía un mensaje al actor A. B sigue a A
        actorA.tell(new Follow(),actorC); // C sigue a A

        actorB.tell(new Follow(),actorD); // D sigue a B
        actorB.tell(new Follow(),actorC); // D sigue a B

        // tiempo de espera
        try {
            Thread.sleep(1000);
        } catch (Exception e) {
            System.out.println(e);
        }

        // OBTENER LA LISTA DE SEGUIDORES
        // Obtener la lista de seguidores
        actorA.tell(new User.GetListFollow(),ActorRef.noSender());

        // tiempo de espera
        try {
            Thread.sleep(1000);
        } catch (Exception e) {
            System.out.println(e);
        }

        actorB.tell(new User.GetListFollow(),ActorRef.noSender());

        try {
            Thread.sleep(1000);
        } catch (Exception e) {
            System.out.println(e);
        }

        // PUBLICACIONES
        // Realizar una publicación
        Publication publicacion1 = new Publication("Publicación: Esta es la publicación del Actor A");
        actorA.tell(publicacion1,ActorRef.noSender());

        // Detiene el sistema de actores hasta que mensajes se procesen
        system.terminate();

    }
}