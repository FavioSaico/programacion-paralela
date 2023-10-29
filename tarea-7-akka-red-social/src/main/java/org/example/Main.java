package org.example;

import akka.actor.ActorSystem;
import akka.actor.ActorRef;
import akka.actor.Props;

public class Main {

    // creamos una función para colocar un tiempo espera, esto para poder mostrar mejor los resultados
    // dado que los actores se ejecutan en paralelo, un actor puede imprimir los mensajes antes que otro y mostrar los resultados desordenados
    public static void esperar(int time){
        try {
            Thread.sleep(time);
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static void main(String[] args) {

        // Crea el sistema de actores
        ActorSystem system = ActorSystem.create("CadenaActores");

        // Crea los actores o usuario para este caso
        ActorRef actorD = system.actorOf(Props.create(User.class, "ActorD"));
        ActorRef actorC = system.actorOf(Props.create(User.class, "ActorC"));
        ActorRef actorB = system.actorOf(Props.create(User.class, "ActorB"));
        ActorRef actorA = system.actorOf(Props.create(User.class, "ActorA"));


        // ENVIAR MENSAJES
        // asumimos que los mensajes se pueden enviar desde cualquier actor a otro, no es necesario seguirlo.
        // esto lo hacemos enviando la clase MensajeCadena
        MensajeCadena ms = new MensajeCadena("Hola como estas");
        actorA.tell(ms,actorB);
        esperar(1000);
        System.out.println();


        // AGREGAR SEGUIDOR
        // agregamos seguidores a nuestros usuarios a traves de clase Follow
        actorA.tell(new Follow(),actorB); // // actor B envía un mensaje al actor A. B sigue a A
        actorA.tell(new Follow(),actorC); // C sigue a A

        actorB.tell(new Follow(),actorD); // D sigue a B
        actorB.tell(new Follow(),actorC); // C sigue a B
        esperar(1000);
        System.out.println();


        // OBTENER LA LISTA DE SEGUIDORES
        // Obtenemos la lista de seguidore del usuario A, pasando la clase GetListFollow() que definimos dentro de User
        actorA.tell(new User.GetListFollow(),ActorRef.noSender());
        esperar(1000);

        // Obtenemos la lista de seguidores del usuario B
        actorB.tell(new User.GetListFollow(),ActorRef.noSender());
        esperar(1000);
        System.out.println();


        // PUBLICACIONES
        // Realizamos una publicación, esta publicación la realiza el usuario A.
        Publication publicacion1 = new Publication("Publicación: Esta es la publicación del Actor A");
        actorA.tell(publicacion1,ActorRef.noSender());
        esperar(1000);
        System.out.println();
        // Detiene el sistema de actores hasta que los mensajes se procesen
        system.terminate();

    }
}