
export const calculateWinner = (squares) => {
    const row = [[0, 0, 0], [0, 0, 0]];
    const col = [[0, 0, 0], [0, 0, 0]];
    const d1 = [0, 0];
    const d2 = [0, 0];

    for (let i = 0; i < squares.length; i++) {
        if (squares[i] === null)
            continue;

        const r = Math.floor(i / 3);
        const c = i % 3;
        const id = squares[i] === 'X' ? 0 : 1;

        row[id][r]++;
        col[id][c]++;

        if (r === c) d1[id]++;
        if (r + c === 2) d2[id]++;

        if (row[id][r] === 3 || col[id][c] === 3 || d1[id] === 3 || d2[id] === 3)
            return id === 0 ? 'X' : 'O';
    }

    return null;
};

export const findBestMove = (squares) => {
    let bestVal = -1000;
    let bestMove = { row: -1, col: -1 };

    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            if (squares[i * 3 + j] === null) {
                let newSquares = [...squares];
                newSquares[i * 3 + j] = 'O';
                let moveVal = minMax({ squares: newSquares, depth: 0, isMax: false });
                newSquares[i * 3 + j] = null;
                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove.row * 3 + bestMove.col;
};

const evaluateScore = (squares) => {
    if (calculateWinner(squares) === 'O')
        return +10;
    else if (calculateWinner(squares) === 'X')
        return -10;
    return 0;
};

const minMax = ({ squares, depth, isMax }) => {
    let score = evaluateScore(squares);

    if (score === 10 || score === -10)
        return score;
    if (!isMoveLeft(squares))
        return 0;
    if (isMax) {
        let best = -1000;
        for (let i = 0; i < 3; i++) {
            for (let j = 0; j < 3; j++) {
                if (squares[i * 3 + j] === null) {
                    let newSquares = [...squares];
                    newSquares[i * 3 + j] = 'O';
                    best = Math.max(best, minMax({ squares: newSquares, depth: depth + 1, isMax: !isMax }));
                    newSquares[i * 3 + j] = null;
                }
            }
        }
        return best;
    }
    else {
        let best = 1000;
        for (let i = 0; i < 3; i++) {
            for (let j = 0; j < 3; j++) {
                if (squares[i * 3 + j] === null) {
                    let newSquares = [...squares];
                    newSquares[i * 3 + j] = 'X';
                    best = Math.min(best, minMax({ squares: newSquares, depth: depth + 1, isMax: !isMax }));
                    newSquares[i * 3 + j] = null;
                }
            }
        }
        return best;
    }
};

const isMoveLeft = (squares) => {
    return squares.some((square) => square === null);
};
