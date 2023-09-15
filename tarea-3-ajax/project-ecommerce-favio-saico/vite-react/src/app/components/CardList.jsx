import { useEffect, useState } from "react"
import { Card } from "./Card"


export const CardList = () =>{ // debe recibir de parametro a publisher, sea DC o Marvel

    const [products, setProducts] = useState();
    useEffect(()=>{
        setTimeout(()=>{
            // PETICIÓN
            fetch("http://localhost:3003/api/product")
            .then(response => response.json()) // leemos la api en formato JSON
            .then(data => setProducts(data))
        },1000)
    },[])

    console.log(products)
    return(
        // una columna en movil, 3 columnas en mediano
        <div className="row row-cols-1 row-cols-md-2 row-cols-lg-3 g-3">
            {
                products ? (
                    products.map(product => (
                        <Card
                            key={product._id}
                            {...product}
                        />
                    ))
                ):(
                    <p>Cargando...</p>
                )
                
            }
        </div>
    )
}