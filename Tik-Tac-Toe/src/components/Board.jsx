import React, { useEffect } from "react";
import { useToast } from '@chakra-ui/react';
import Square from "./Square";
import { calculateWinner, findBestMove } from "../Game";
import { GameState } from "./context";

const Board = () => {
    const { squares, setSquares, isXPlaying, setIsXPlaying, count, setCount } = GameState();
    const toast = useToast();

    let timeoutTime = 5000;

    useEffect(() => {
        if (!isXPlaying && calculateWinner(squares) === null) {
            const bestMove = findBestMove(squares);
            const newSquares = [...squares];
            const updatedCount = count+1;
            newSquares[bestMove] = 'O';
            setSquares(newSquares);
            setCount(updatedCount);

            const winner = calculateWinner(newSquares);
            if (winner !== null) {
                handleWinner(winner);
                return;
            }
            setIsXPlaying(!isXPlaying);
        }

    }, [isXPlaying, squares]);


    const handleWinner = (winner) => {
        toast({
            position: 'bottom',
            title: "Match Over",
            description: `Winner is ${winner}`,
            status: 'success',
            duration: timeoutTime,
            isClosable: true,
        });
        setTimeout(() => {
            handleRestart();
        }, timeoutTime);
    };

    const handleDraw = () => {
        toast({
            position: 'bottom',
            title: "Match Over",
            description: "It's a draw",
            status: 'success',
            duration: timeoutTime,
            isClosable: true,
        });
        setTimeout(() => {
            if(count===9)
                handleRestart();
        }, timeoutTime);
    };

    const handleRestart = () => {
        setSquares(Array(9).fill(null));
        let temp = timeoutTime;
        timeoutTime = 0;
        setIsXPlaying(true);
        timeoutTime = temp;
        setCount(0);
    };

    const handleClick = (i) => {
        
        const newSquares = [...squares];
        const updatedCount = count + 1;
        if (newSquares[i] === null && isXPlaying === true) {
            newSquares[i] = isXPlaying ? 'X' : 'O';
            setSquares(newSquares);
            setIsXPlaying(!isXPlaying);
            setCount(updatedCount);
            if (updatedCount >= 5 && updatedCount <= 9) {
                const winner = calculateWinner(newSquares);
                if (winner !== null) {
                    handleWinner(winner);
                    return;
                }
                if (winner === null && updatedCount === 9) {
                    console.log("hanlde draw1");
                    handleDraw();
                    return;
                }
            }
        }
        console.log("count = "+updatedCount);
        if (updatedCount === 9) {
            console.log("hanlde draw2");
            handleDraw();
            return;
        }
    };

    const buttonStyle = {
        margin: "10px",
    };

    return (
        <div className="board-container" style={{ display: "flex", flexDirection: "column", alignItems: "center" }}>
            <div className="status">Status</div>
            <div className="row">
                <div className="col">
                    <Square value={squares[0]} onClick={() => handleClick(0)} />
                    <Square value={squares[1]} onClick={() => handleClick(1)} />
                    <Square value={squares[2]} onClick={() => handleClick(2)} />
                </div>
            </div>
            <div className="row">
                <div className="col">
                    <Square value={squares[3]} onClick={() => handleClick(3)} />
                    <Square value={squares[4]} onClick={() => handleClick(4)} />
                    <Square value={squares[5]} onClick={() => handleClick(5)} />
                </div>
            </div>
            <div className="row">
                <div className="col">
                    <Square value={squares[6]} onClick={() => handleClick(6)} />
                    <Square value={squares[7]} onClick={() => handleClick(7)} />
                    <Square value={squares[8]} onClick={() => handleClick(8)} />
                </div>
            </div>
            <button className='btn btn-primary' style={buttonStyle} onClick={handleRestart}>Restart</button>
        </div>
    );
};

export default Board;
