import { Link } from "react-router-dom"
import { CardList } from "../components/CardList"

export const MainPage = () =>{

    return(
        <div className="container mt-3">
            <header className="d-flex align-items-center justify-content-between">
                <h1>Lista de productos</h1>

                <div>
                    <Link to='/auth/login' className="btn btn-primary m-2">Iniciar sesión</Link>
                    <Link to='/auth/register' className="btn btn-primary">Registrarse</Link>
                </div>
            </header>
            <hr />
            
            <CardList/>
            
        </div>
    )
}