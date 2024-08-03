
import logo1 from "../assets/1.jpg"
import logo2 from "../assets/2.png"
import logo3 from "../assets/3.jpg"
import logo4 from "../assets/4.jpg"

const logos = [
    logo1,
    logo2,
    logo3,
    logo4,
]

const GridElement: React.FC<{
    logoIndex: number;
    visible?: boolean;
}> = ({logoIndex, visible}) => {
    if(!visible) {
        return <div className="hidden-image"></div>
    }
    return <img src={logos[logoIndex]} alt="logo" width={64} height={64} />
    // return <img src={`/assets/${logoIndex}.jpg`} alt="logo" width={64} height={64} />
}

export default GridElement