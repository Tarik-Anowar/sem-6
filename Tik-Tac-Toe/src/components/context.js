import React, { createContext, useContext, useState } from "react";

const GameContext = createContext();

const ContextProvider = ({ children }) => {
    const [squares, setSquares] = useState(Array(9).fill(null));
    const [isXPlaying, setIsXPlaying] = useState(true);
    const [count, setCount] = useState(0);
    return (
        <GameContext.Provider value={{ squares, setSquares,isXPlaying, setIsXPlaying,count, setCount }}>
            {children}
        </GameContext.Provider>
    );
};

export const GameState = () => {
    return useContext(GameContext);
};

export default ContextProvider;
