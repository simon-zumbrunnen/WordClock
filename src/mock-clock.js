const { screen, text } = require('blessed');

const clock = screen({
    smartCSR: true
});

const letters = [
    'INHÄZNITHCA',
    'ELFISIEBNIE',
    'IFLÖWZIREIV',
    'ZWEISÄCHSIE',
    'IFIÖFÜRDSIE',
    'HALBISNÜNIE',
    'HEBASROVIÖN',
    'AZÄHEZWÄNZG',
    'FIÖFLETREIV',
    'ESBISCHDSON'
];

for (let row = 0; row < letters.length; row++) {   
    for (let column = 0; column < letters[0].length; column++) {
        const letter = text({
            content: letters[row][column],
            top: letters.length - 1 - row,
            left: row%2 === 0 ? letters[0].length - 1 - column : column,
            style: {
                fg: 'black',
                bg: 'black'
            }
        });

        clock.append(letter);
    }
}

module.exports = {
    all: (r, g, b, a=1) => {
        for (let letter of clock.children) {
            letter.style.transparent = a < 1;
            letter.style.fg = r ? 'white' : 'black';
        }
    },
    set: (n, r, g, b, a=1) => {

        const letter = clock.children[n]

        letter.style.transparent = a < 1;
        letter.style.fg = r ? 'white' : 'black';
    },
    sync: () => {
        clock.render();
    }
}
