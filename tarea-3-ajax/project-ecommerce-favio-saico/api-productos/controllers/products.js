const { response } = require('express');
const {Producto}= require('../models');
const axios = require('axios');
const path = require('path');
const fs = require('fs');

const obtenerProductos = async(req, res = response ) => {

    const productos = await Producto.find({});

    
    if ( !productos ) {
        return res.status(400).json({ // estatus 400, porque es un error de correo o contraseña, no es error del servidor
            msg: 'No hay productos' // error en el correo
        });
    }

    res.json(
        // total,
        productos
    );
}


const obtenerProducto = async(req, res = response) =>{
    const { id } = req.params;
    // console.log(id)
    const producto = await Producto.findById( id );
    // console.log(producto)
    res.json( producto );
}

const crearProducto = async(req, res = response ) => {

    const { name,description,stock,price, img} = req.body;

    // Generar la data a guardar
    const data = {
        name,description,stock,price,img
    }

    const producto = new Producto( data ); // creamos un producto, empata con el modelo

    // Guardar en la DB
    await producto.save();

    res.status(201).json(producto); // producto

}

module.exports = {
    obtenerProductos,
    crearProducto,
    obtenerProducto
}