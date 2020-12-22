const socket = io("ws://localhost:8080")

socket.on('message', (text) => {
  const el = document.createElement('h1');
  el.innerHTML = text;
  document.querySelector('.main').appendChild(el);
});