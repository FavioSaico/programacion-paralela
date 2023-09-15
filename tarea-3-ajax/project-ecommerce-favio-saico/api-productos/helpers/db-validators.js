const { Producto,Usuario } = require('../models');

const existeProductoPorId = async( id ) => {

    // Verificar si el correo existe
    const existeProducto = await Producto.findById(id);
    
    if ( !existeProducto ) {
        throw new Error(`El id ${ id } no existe`);
    }
}

const emailExiste = async( email = '' ) => {

    // Verificar si el correo existe
    const existeEmail = await Usuario.findOne({ email })
    if ( existeEmail ) { // si existe no podemos registrarlo.
        throw new Error(`El correo: ${ email}, ya está registrado`); // el mensaje aparece en formato json
    }
}

const existeclientePorId = async( id ) => {

    // Verificar si el correo existe
    const existeCliente = await Usuario.findById(id);
    
    if ( !existeCliente ) {
        throw new Error(`El id ${ id } no existe`);
    }
}

module.exports = {
    existeProductoPorId,
    emailExiste,
    existeclientePorId
}