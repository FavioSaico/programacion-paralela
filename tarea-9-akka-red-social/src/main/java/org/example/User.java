package org.example;

import akka.actor.AbstractActor;
import akka.actor.ActorRef;

import java.util.ArrayList;
import java.util.List;

public class User extends AbstractActor {

    private final String nombre;
    private List<ActorRef> UserFollow;
    public User(String nombre) {
        this.nombre = nombre;
        this.UserFollow = new ArrayList<>();
    }

    public static class GetListFollow{}

    // acciones que realiza al recibir mensajes
    @Override
    public AbstractActor.Receive createReceive() {
        return receiveBuilder()
                .match(MensajeCadena.class, mensaje -> { // ENVIAR MENSAJES
                    // Agrega información al mensaje, le añade el nombre del actor emisor y receptor
                    getSender().tell(new ShowMessage(" envio '" + mensaje.getContenido() + "' a " + nombre),ActorRef.noSender());

                })
                .match(Follow.class, seguir -> { // AGREGAR SEGUIDOR
                    // UserFollow es del actor receptor
                    // getSender es el acto que envia el mensaje
                    UserFollow.add(getSender()); // Añadimos al emisor a la lista de seguidores

                    String content = " sigue a " + nombre;
                    getSender().tell(new ShowMessage(content),ActorRef.noSender());
                })
                .match(GetListFollow.class, text ->{ // OBTENER LA LISTA DE SEGUIDORES
                    System.out.printf("Lista de seguidores de " + nombre + "\n");
                    System.out.printf("Cantidad de seguidores: " + UserFollow.size() + "\n");
                    // Mostramos el nombre de los seguidores
                    UserFollow.forEach(actorRef ->
                            actorRef.tell(new ShowMessage( ""), ActorRef.noSender())
                    );

                })
                .match(Publication.class, publication-> { // PUBLICACIONES
                    System.out.printf(publication.getContenido() + "\n");
                    System.out.printf("Enviando publicación a los seguidores..." + "\n");

                    UserFollow.forEach(actorRef ->
                            actorRef.tell(new ShowMessage(" recibo la publicación de " + nombre), ActorRef.noSender())
                    );
                })
                .match(ShowMessage.class, message-> { // IMPRIMIR POR CONSOLA
                        System.out.printf(nombre + message.getContent() + "\n");

                })
                .build();
    }

}
