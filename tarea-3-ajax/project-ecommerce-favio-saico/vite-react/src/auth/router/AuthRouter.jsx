import { Navigate, Route, Routes } from "react-router-dom"
import { LoginPage, RegisterPage } from "../pages"

export const AuthRouter = () =>{

    return(
        <Routes>
            {/* Establecemos las rutas para auth */}
            {/* como estan dentro de /auth, el route le agregra el path a la ruta, generando /auth/login y /auth/register */}
            <Route path="login" element={<LoginPage/>} />
            <Route path="register" element={<RegisterPage/>} />

            <Route path="/*" element={<Navigate to="/auth/login"/>} />

        </Routes>
    )
}