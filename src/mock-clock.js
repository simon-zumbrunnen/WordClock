const clock = [
    'ESBISCHDSON',
    'VIERTELFÖIF',
    'AZÄHEZWÄNZG',
    'NÖIVORSABEH',
    'HALBISNÜNIE',
    'EISDRÜFÖIFI',
    'ZWEISÄCHSIE',
    'VIERIZWÖLFI',
    'ELFISIEBNIE',
    'ACHTINZÄHNI'
];

let colors = [];

for (let row = 0; row < clock.length; row++) {
    let rowColors = [];
    
    for (let letter = 0; letter < clock[0].length; letter++) {
        rowColors.push([0, 0, 0]);
    }

    colors.push(rowColors);
}

module.exports = {
    all: (r, g, b, a=1) => {
        for (let row = 0; row < clock.length; row++) {            
            for (let letter = 0; letter < clock[0].length; letter++) {
                colors[row][letter] = [r*a, g*a, b*a];
            }
        }
    },
    set: (n, r, g, b, a=1) => {
        const row = Math.ceil((n + 1)/(clock[0].length)) - 1;
        const letter = n%clock[0].length;

        if (row%2 === 0) {
            colors[row][letter] = [r*a, g*a, b*a];
        } else {
            colors[row][clock[0].length - 1 - letter] = [r*a, g*a, b*a];
        }
    },
    sync: () => {
        console.log('-----------')
        for (let row = 0; row < clock.length; row++) {
            let rowText = '';
            for (let letter = 0; letter < clock[0].length; letter++) {
                if (colors[row][letter][0] === 255) {
                    rowText += clock[row][letter];
                } else {
                    rowText += ' ';
                }
            }

            console.log(rowText);
        }
    }
}
