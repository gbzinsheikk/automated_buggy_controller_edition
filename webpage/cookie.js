// Função para criar ou atualizar um cookie
function setCookie(name, value, days) {
    let expires = "";
    if (days) {
        const date = new Date();
        date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
        expires = "; expires=" + date.toUTCString();
    }
    document.cookie = name + "=" + encodeURIComponent(value) + expires + "; path=/";
}

// Função para ler um cookie
function getCookie(name) {
    const nameEQ = name + "=";
    const cookies = document.cookie.split(';');
    for (let i = 0; i < cookies.length; i++) {
        console.log('opa',cookies.length);
        let c = cookies[i].trim(); // Remove espaços antes e depois
        console.log("Analisando cookie:", c);
        if (c.indexOf(nameEQ) === 0) { // Verifica se começa com nameEQ
            console.log("Cookie encontrado:", c);
            return decodeURIComponent(c.substring(nameEQ.length, c.length));
        }
    }
    console.log("Cookie não encontrado:", nameEQ);
    return null; // Retorna null se não encontrado
}


// Função para deletar um cookie
function deleteCookie(name) {
    document.cookie = name + "=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;";
}

// Inicializar array para guardar a ordem
let buttonOrder = [];

// Capturar cliques nos botões
document.querySelectorAll('button[id^="btn"]').forEach(button => {
    button.addEventListener('click', () => {
        const buttonId = button.id; // Captura o ID do botão
        buttonOrder.push(buttonId); // Armazena no array
        setCookie('buttonOrder', buttonOrder.join(','), 1); // Salva no cookie
        console.log(`Botão pressionado: ${buttonId}`);
    });
});

// Mostrar a ordem dos cliques
function showOrder() {
    const savedOrder = getCookie('buttonOrder');
    console.log('Cookie recuperado:', getCookie('buttonOrder'))
    console.log('Cookie recuperado:', savedOrder); // Adicionado para debug
    const output = document.getElementById('output');
    if (savedOrder) {
        const order = savedOrder.split(',');
        output.textContent = `Ordem dos botões pressionados: ${buttonOrder.join(' , ')}`;
        console.log('awge');
    } else {
        output.textContent = 'Nenhum botão foi pressionado ainda!';
        console.log('asdf');
    }
}

// Limpar a ordem dos cliques
function clearOrder() {
    deleteCookie('buttonOrder');
    buttonOrder = [];
    const output = document.getElementById('output');
    output.textContent = 'A ordem foi limpa!';
    alert('Ordem dos cliques apagada!');
}
