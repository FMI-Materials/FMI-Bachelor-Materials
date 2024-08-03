import {
    Link
} from 'react-router-dom';
import GridElement from "../components/GridElement";
import {PageContainer} from "../components/PageContainer"

const data = [
    [0, 1, 2, 3],
    [0, 1, 2, 3],
    [0, 1, 2, 3],
];

const Game = () => {
    return (
        <PageContainer>
        <>

            <h1>Game</h1>
            {/*<Link to="/profile">go to profile</Link>*/}
            {
                data.map((row) => (
                    <div className="row">
                        {row.map(col=>(
                            <div className="col">
                                <GridElement logoIndex={col} visible={true} />
                            </div>
                        ))}
                    </div>
                ))
            }
        </>
        </PageContainer>

    );
}

export default Game;