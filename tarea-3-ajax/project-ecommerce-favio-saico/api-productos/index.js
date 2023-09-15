require('dotenv').config(); // .env se establece como variable de entorno

const Server = require('./models/server');
const server = new Server(); // ya se tiene el index.html servido y las rutas 
server.listen(); // con esto levantamos el servidor