// destructramos la función router
const { Router } = require('express');
const { obtenerProductos, crearProducto, obtenerProducto } = require('../controllers/products');
const { check } = require('express-validator');
const { validarCampos } = require('../middlewares/validar-campos');
const { existeProductoPorId } = require('../helpers/db-validators');

const router = Router(); // llamamos la función

router.get('/',obtenerProductos) // función establecida en auth.js de controllers

// producto por id
router.get('/:id',[
    check('id', 'No es un id de Mongo válido').isMongoId(),
    check('id').custom( existeProductoPorId ),
], obtenerProducto)

// Crear producto - privado - cualquier persona con un token válido
router.post('/', [ 
    check('name','El nombre es obligatorio').not().isEmpty(),
    // check('img','La imagen es obligaria').not().isEmpty(),
    validarCampos
], crearProducto );

module.exports = router;