const mongoose = require('mongoose')

const dbConnection = async () =>{
    //
    try {
        // regresa una promesa
        const mongoUrl = process.env.MONGODB || process.env.MONGODB_CNN

        await mongoose.connect(mongoUrl, { // pasamo el link y un objeto con ciertas propiedades
            useNewUrlParser: true,
            useUnifiedTopology: true
        });

        console.log('Base de datos conectada');
    } catch (error) { // por si da error
        console.log(error)
        throw new Error('Error de conección a la base de datos')
    }

}

module.exports = {
    dbConnection
}
