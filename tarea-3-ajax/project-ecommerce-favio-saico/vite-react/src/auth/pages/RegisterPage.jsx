import { useState }from "react"
import {Navigate, Link} from "react-router-dom"
import "./styles.css"

import seePass from '../../assets/eye-line.svg';
import notSeePass from '../../assets/eye-off-line.svg';

export const RegisterPage = () =>{

    const [name, setName] = useState ('')
    const [lastname, setLastname] = useState ('')
    const [email, setEmail] = useState ('')
    const [password, setPassword] = useState ('')

    const [seePassword, setSeePassword] = useState(false);

    const [message, setMessage] = useState({
        state: false,
        message: ""
    });

    const onSubmit = (e) =>{
        e.preventDefault();
        const data = {
            name,
            lastname,
            email,
            password
        }
        // console.log(data);
        // PETICIÓN
        fetch("http://localhost:3003/api/auth/registration", {
            method: 'POST',
            body: JSON.stringify(data),
            headers: {
                'Content-Type': 'application/json',
            }
        })
        .then(response => response.json()) // leemos la api en formato JSON
        .then(data => {
            console.log(data);

            if(data.usuario == null ){
                setMessage({
                    state: true,
                    message:"Error al registrarse"
                });
            }else{
                setMessage({
                    state: true,
                    message:"Regristrado correctamente"
                });
            }
        })
    }

    function handleChangeName(event) {
        setName(event.target.value);
    }
    function handleChangeCorreo(event) {
        setEmail(event.target.value);
    }
    function handleChangePass(event) {
        setPassword(event.target.value);
    }
    function handleChangeLastname(event) {
        setLastname(event.target.value);
    }

    return(
        <div className="container-2 d-flex align-items-center">
            <form className="form" onSubmit={onSubmit}>
                <h2 className="form__title">Registrarse</h2>
                <p className="form__paragraph">¿Ya tienes cuenta? <Link to='/auth/login' className="form__link">Iniciar sesión</Link></p>
                
                <div className="form__container">
                    <div className="form__group">
                        <input type="text" id="name" className="form__input" placeholder="Nombre" value={name} onChange={handleChangeName} required/>
                        {/* <span className="form__line"></span> */}
                    </div>
                    <div className="form__group">
                        <input type="text" id="lastname" className="form__input" placeholder="Apellidos" value={lastname} onChange={handleChangeLastname} required/>
                        {/* <span className="form__line"></span> */}
                    </div>
                    <div className="form__group">
                        <input type="email" id="email" className="form__input" placeholder="Correo electrónico" value={email} onChange={handleChangeCorreo} required/>
                        {/* <span className="form__line"></span> */}
                    </div>
                    <div className="form__group form__input_pass">
                        <input type={seePassword ? "text":"password"} id="password" className="form__input" placeholder="Contraseña" value={password} onChange={handleChangePass} required/>
                        <div className="btn_pass" onClick={()=>setSeePassword(!seePassword)}>
                            <img src={seePassword ?  notSeePass : seePass} alt="" className="see"/>
                        </div>
                    </div>
                    <input type="submit" className="btn btn-primary" value="Registrar"/>
                </div>
                {
                    message.state && (
                        <>
                            <p>{message.message}</p>
                            <p><Navigate to="/auth/login"/></p>
                        </>
                    )
                }
            </form>
            
        </div>
    )
}
