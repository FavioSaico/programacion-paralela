const { response } = require('express');
const Usuario = require ('../models/user');

const obtenerClientes = async (req, res = response) => {

    const clientes = await Usuario.find({});

    
    if ( !clientes ) {
        return res.status(400).json({ 
            msg: 'No hay clientes'
        });
    }

    res.json(
        clientes
    );
}

const obtenerCliente = async (req, res = response) => {

    const { id } = req.params;
    // console.log(id)
    const cliente = await Usuario.findOne( {_id:id} );

    // console.log(producto)
    res.json( cliente );
}

const login = async(req, res = response) => {

    const { email, password } = req.body;

    try {

        // Verificar si el email existe, buscamos el correo en la base de datos
        const usuario = await Usuario.findOne({ email });
        if ( !usuario ) {
            return res.status(400).json({ // estatus 400, porque es un error de correo o contraseña, no es error del servidor
                msg: 'Usuario / Password no son correctos - correo' // error en el correo
            });
        }

        if(usuario.password != password){
            return res.status(400).json({
                msg: 'Usuario / Password no son correctos - password' // error en el password
            });
        }

        return res.status(200).json({
            usuario
        });

    } catch (error) {
        //console.log(error)
        res.status(500).json({ // estatus 500, porque normalmente será un error interno del servidor.
            msg: 'Hable con el administrador'
        });
    } 

}

const registration = async(req, res = response) => {
       // extraemos los datos que nos interesan, pero si son por ejemplo 1000 datos, podemos solo exparsir la data ({abc,...resto } y resto tendria la data menos abc) 
    const {name, lastname, email, password} = req.body;
    const usuario = new Usuario({name, lastname, email, password}) // el modelo Usuario va a tomar a body y cogerá todos los valores que coincidan con el modelo, si hay información que esta en body y no en el modelo, entonce se ignorará

    // GUARDAMOS
    await usuario.save() // guardamos la data en mongo, esta es una función asincrona porque esperamos la respues de una aplicación externa por la petición

    res.json({
        // body // mandamos directamente el body, no parte por parte
        usuario // mostramos el usuario en formato json
    })
}

module.exports = {
    login,
    registration,
    obtenerCliente,
    obtenerClientes
}