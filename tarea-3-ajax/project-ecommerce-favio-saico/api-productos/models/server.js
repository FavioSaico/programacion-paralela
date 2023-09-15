const express = require('express')
const cors = require('cors');
const { dbConnection } = require('../database/config');

class Server{
    constructor(){
        // creamos el servidor
        this.app = express(); 
        this.port = process.env.PORT;

        this.paths = { // objeto con todas las rutas
            product:'/api/product',
            auth:'/api/auth'
        }

        // Conectar a la base de datos
        this.conectarDB();

        // middlewares
        this.middlewares();

        // definimos las rutas de la aplicación
        this.routes();

    }

    async conectarDB () { // creamos la función para conectar a la base de datos
        await dbConnection();
    }

    middlewares(){
        // use - es el termino que dice que este es un middleware
        //cors
        this.app.use(cors())
        
        //Lectura y parseo del body
        this.app.use(express.json());// cualquier información que venga de POST, PUT o DELETE (incluso GET)se va a serializar en formato JSON

    }

    routes(){// metodo para el manejo de las clases
        // aplicamos un middleware, pero para la ruta, es como un condicional para que solo aplicaque en esa ruta
        // lo que carga en esa ruta es el archivo de ruta user (ruta de los usuarios)
        // this.app.use(this.usuariosPath,require('../routes/user'))
        // this.app.use(this.authPath,require('../routes/auth')) // mostrará lo del archivo auth.js de routes

        // establecemos las rutas, las sub rutas de cada ruta
        this.app.use( this.paths.product, require('../routes/product'));
        this.app.use( this.paths.auth, require('../routes/auth'));
    }

    listen(){
        this.app.listen(this.port, ()=>{
            console.log('Servidor en el puerto ', this.port)
        })
    }

}

module.exports = Server;
