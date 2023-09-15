// destructramos la función router
const { Router } = require('express');
const { check } = require('express-validator');

const {validarCampos} = require('../middlewares/validar-campos')
const { login,registration, obtenerCliente, obtenerClientes } = require('../controllers/auth');
const { emailExiste, existeclientePorId} = require('../helpers/db-validators');

const router = Router(); // llamamos la función

// Obtener lista de usuarios
router.get('/',obtenerClientes) // función establecida en auth.js de controllers

// Obtener usuario por id
router.get('/:id',[
    check('id', 'El id no es válido').isMongoId(),
    check('id').custom( existeclientePorId ),
    validarCampos
],obtenerCliente) // función establecida en auth.js de controllers

// Logeo del usuario
router.post('/login',[
    check('email', 'El correo no es válido').isEmail(),
    check('password', 'La contraseña es obligatoria').not().isEmpty(),
    // validarCampos
],login) // función establecida en auth.js de controllers

// Registro del usuario
router.post('/registration',[
    check('name', 'El nombre es obligatorio').not().isEmpty(),// not().isEmpty(): no tiene que estar vacio
    check('lastname', 'Los apellidos son obligatorios').not().isEmpty(),
    check('password', 'El password debe de ser más de 6 letras').isLength({ min: 6 }), // minimo de 6 letras
    check('email','El correo no es válido').isEmail(), // check es un middleware al que podemos mandar el campo que va a revisar y el mensaje por si no es valido
    check('email').custom( emailExiste ),
    validarCampos
],registration)

module.exports = router;

// (req, res = response) => {
//     return res.status(400).json({
//         msg: 'Usuario / Password no son correctos - password' // error en el password
//     });
// }