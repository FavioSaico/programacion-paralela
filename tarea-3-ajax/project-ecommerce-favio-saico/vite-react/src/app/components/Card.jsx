import './styles.css'

export const Card = ({ // recibimos cada una de las props del hero
    name="Samsung 970 EVO",
    description= "Plus SSD 2TB NVMe M.2 Disco duro interno de estado sólido",
    price=89.99,
    img="https://m.media-amazon.com/images/I/51Brl+iYtvL._AC_SX679_.jpg"

}) =>{
    return(
        <div className="col">    
            <div className="card h-100">
                    <div className="d-flex justify-content-center">
                        <img src={img} className="img-vertical" alt='image' />
                    </div>
                    <div className="">
                        <div className="card-body">
                            <h5 className="card-title">{name}</h5>
                            <p className="card-text">{description}</p>
                            <p className="card-text " >
                                <small className="text-muted fs-5">US${price}</small>
                            </p>

                        </div>
                    </div>
            </div>
            </div>
    )
}
