import { Route, Routes } from "react-router-dom"
import { MainRouter } from "../app/router/MainRouter"
import { AuthRouter } from "../auth/router/AuthRouter"

export const AppRouter = () =>{

    return(
        <>
            {/* definimos las rutas de la pagina, por cada ruta hay una página */}
            <Routes>
                {/* <Route path="marvel" element = { <MarvelPage/> }/>
                <Route path="dc" element = { <DcPage/> }/> */}
                {/* <Route path="login" element = { <LoginPage/> }/> */}
                <Route path="/auth/*" element = { 
                    <AuthRouter/>
                }/>

                <Route path="/*" element = { 
                    <MainRouter/> 
                }/>

                {/* Cualquier otra ruta irá a HeroesRoutes, que tiene almacenada el resto de rutas */}
                {/* <Route path="/*" element = { <HeroesRoutes/> }/> */}

            </Routes>
        </>
    )
}