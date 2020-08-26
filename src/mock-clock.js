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
            top: 1 + letters.length - 1 - row,
            left: row%2 === 0 ? 1 + letters[0].length - 1 - column : 1 + column,
            style: {
                fg: 'black',
                bg: 'black'
            }
        });

        clock.append(letter);
    }
}

const dot0 = text({
    content: '.',
    top: 0,
    left: 2 + letters[0].length - 1,
    style: {
        fg: 'black',
        bg: 'black'
    }
});

clock.append(dot0);

const dot1 = text({
    content: '.',
    top: 0,
    left: 0,
    style: {
        fg: 'black',
        bg: 'black'
    }
});

clock.append(dot1);

const dot2 = text({
    content: '.',
    top: 1 + letters.length - 1,
    left: 2 + letters[0].length - 1,
    style: {
        fg: 'black',
        bg: 'black'
    }
});

clock.append(dot2);

const dot3 = text({
    content: '.',
    top: 1 + letters.length - 1,
    left: 0,
    style: {
        fg: 'black',
        bg: 'black'
    }
});

clock.append(dot3);

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
