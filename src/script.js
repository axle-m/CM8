// FEN starting position
let currentFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
const boardDiv = document.getElementById("board");

const pieceMap = {
  'P': 'wp.png',
  'N': 'wn.png',
  'B': 'wb.png',
  'R': 'wr.png',
  'Q': 'wq.png',
  'K': 'wk.png',
  'p': 'bp.png',
  'n': 'bn.png',
  'b': 'bb.png',
  'r': 'br.png',
  'q': 'bq.png',
  'k': 'bk.png'
};

function drawBoard(fen) {
  boardDiv.innerHTML = "";
  const [position] = fen.split(" ");
  const rows = position.split("/");

  for (let row = 0; row < 8; row++) {
    const squares = rows[row];
    let col = 0;

    for (const char of squares) {
      if (isNaN(char)) {
        const piece = document.createElement("img");
        piece.src = `img/${pieceMap[char]}`;
        const square = document.createElement("div");
        square.className = `square ${(row + col) % 2 === 0 ? "white" : "black"}`;
        square.appendChild(piece);
        boardDiv.appendChild(square);
        col++;
      } else {
        for (let i = 0; i < parseInt(char); i++) {
          const square = document.createElement("div");
          square.className = `square ${(row + col) % 2 === 0 ? "white" : "black"}`;
          boardDiv.appendChild(square);
          col++;
        }
      }
    }
  }
}

async function sendMoveToServer() {
  try {
    const res = await fetch('http://localhost:8000/play', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ fen: currentFEN })
    });

    const data = await res.json();
    currentFEN = data.fen;
    drawBoard(currentFEN);
  } catch (err) {
    alert("Server error. Make sure the Java server is running.");
    console.error(err);
  }
}

drawBoard(currentFEN);
