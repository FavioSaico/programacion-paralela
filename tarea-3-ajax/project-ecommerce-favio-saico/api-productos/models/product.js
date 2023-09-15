// extraemos el esquema y el modelo
const {Schema, model} = require('mongoose')

const ProductSchema = Schema({ // Shema define cada uno de los campos del usuario
    name:{
        type: String,
        unique: true,
        required: [true, 'El nombre es obligatorio'] // podemos pasar solo true, pero tmb nos permite pasar un mensaje de error
    },
    description: { 
        type: String,
        required: [true, 'Las descripción es obligatorio'] 
    }, 
    stock:{
        type: Number,
        default: 0,
        required: [true, 'El stock es obligatorio']
    },
    price:{
        type: Number,
        default: 0.0, // valos por defecto de cero
        required: [true, 'El precio es obligatorio']
    },
    img:{
        type: String,
        required: [true, 'La imagen es obligatoria']
    }
});

// reescribimos el metodo toJSON
ProductSchema.methods.toJSON = function () { // debe ser una función normal porque el this mantiene la referencia en la misma función.
    const { __v, estado, ...data  } = this.toObject();
    return data;
}

// exportamos el model; este pide el nombre de la colección, que es Usuario (mongosse añade la s al final del nombre) y pide tmb el shema
module.exports = model('Products', ProductSchema);