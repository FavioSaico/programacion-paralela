package org.example;

import akka.actor.AbstractActor;
import akka.actor.ActorRef;

import java.util.ArrayList;
import java.util.List;

// Clase User que extiene de AbstractActor para crear actores en base a esta clase
public class User extends AbstractActor {

    // Cada actor tendrá un nomnre una lista de seguidores, que son otros actores.
    private final String nombre;
    private List<ActorRef> UserFollow;

    // Cada vez que instanciemos esta clase debemos pasar el nombre del usuario.
    // Automaticamente se inicializa el arreglo de usuario como un ArrayList
    public User(String nombre) {
        this.nombre = nombre;
        this.UserFollow = new ArrayList<>();
    }

    // Clase estatica para obtener el nombre de lo seguidores del usuario.
    public static class GetListFollow{}

    // Acciones que realiza al recibir mensajes
    @Override
    public AbstractActor.Receive createReceive() {
        return receiveBuilder()
                // ENVIAR MENSAJES
                // Cuando se envia al usuario la clase MensajeCadena, este debe mostrar el mensaje que se envío sumado al nombre del actor emisor
                // para obtener el nombre del actor emisor del mensaje, debemos enviar un mensaje con la clase ShowMessage al emisor.
                .match(MensajeCadena.class, mensaje -> {
                    getSender().tell(new ShowMessage(" envio '" + mensaje.getContenido() + "' a " + nombre),ActorRef.noSender());

                })
                // AGREGAR SEGUIDOR
                // Para agregar un nuevo seguidor se debe enviar como mensaje la clase Follow,
                // Luego añadimos al usuario emisor a la lista del seguidores del usuario receptor
                // Por ultimo, imprimimos en consola que actor sigue a este actor para confirmar que se agrego.
                .match(Follow.class, seguir -> {
                    UserFollow.add(getSender()); // agrega a la lista

                    String content = " sigue a " + nombre;
                    getSender().tell(new ShowMessage(content),ActorRef.noSender());
                })
                // OBTENER LA LISTA DE SEGUIDORES
                // Para imprimir por consola la lista de seguidores de un usuario debemos enviar la clase GetListFollow
                // Iteremos la lista de seguidores y cada uno le enviamos la clase ShowMessage para que pueda mostrar su nombre.
                .match(GetListFollow.class, text ->{
                    System.out.printf("Lista de seguidores de " + nombre + "\n");
                    System.out.printf("Cantidad de seguidores: " + UserFollow.size() + "\n");
                    // Mostramos el nombre de los seguidores
                    UserFollow.forEach(actorRef ->
                            actorRef.tell(new ShowMessage( ""), ActorRef.noSender())
                    );

                })
                // PUBLICACIONES
                // Para que usuario pueda realizar publicaciones debe recibir la clase Publication
                // Imprimimos por consola el contenido de la publicación e iteramos sobre su lista de siguidores en señal de que recibieron la publicación
                .match(Publication.class, publication-> {
                    System.out.printf(publication.getContenido() + "\n");
                    System.out.printf("Enviando publicación a los seguidores..." + "\n");

                    UserFollow.forEach(actorRef ->
                            actorRef.tell(new ShowMessage(" recibo la publicación de " + nombre), ActorRef.noSender())
                    );
                })
                // IMPRIMIR POR CONSOLA
                // Esta acción recibe la clase ShowMessage para imprimir por consola el nombre y el contenido que venga en la clase
                // esta acción la usuamos en las anteriores para imprimir los nombres de los actores.
                .match(ShowMessage.class, message-> {
                        System.out.printf(nombre + message.getContent() + "\n");

                })
                .build();
    }

}
