
import './App.css';
import Board from './components/Board';
import ContextProvider from './components/context';

function App() {
  const containerStyle = {
    display: "flex",
    flexDirection: "column",
    alignItems: "center",
  };


  return (
    <ContextProvider>
      <Board />
    </ContextProvider>
  );
}

export default App;
