import React from "react";

const Square = ({ value, onClick }) => {
    const squareStyle = {
        color: "black",
        fontSize: "30px",
        width: "120px",
        height: "120px",
        lineHeight: "100px",
        border: "2px solid black",
        borderRadius: "0px"
    };

    return (
        <div className="btn btn-light square" style={squareStyle} onClick={onClick}>
            {value}
        </div>
    );
};

export default Square;
