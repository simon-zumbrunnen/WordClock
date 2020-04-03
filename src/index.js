const IS_DEVELOPMENT = process.env !== 'production';
const LEDMATRIX_NUM_ROWS = 10;
const LEDMATRIX_NUM_COLS= 11;

let clock;

if (IS_DEVELOPMENT) {
    clock = require('./mock-clock');
} else {
    const { Dotstar } = require('dotstar');
    const SPI = require('pi-spi');
    const spi = SPI.initialize('/dev/spidev0.0');
    clock = new Dotstar(spi, {
        length: LEDMATRIX_NUM_ROWS*LEDMATRIX_NUM_COLS
    });
}

const ES_ISCH = [0, 1, 3, 4, 5, 6];
const VIERTEL = [15, 16, 17, 18, 19, 20, 21];
const FOEIF = [11, 12, 13, 14];
const ZAEH = [23, 24, 25];
const ZWAENZG = [27, 28, 29, 30, 31, 32];
const VOR = [38, 39, 40];
const AB = [35, 36];
const HALBI = [44, 45, 46, 47, 48];
const NUENI = [50, 51, 52, 53];
const EIS = [63, 64, 65];
const DRUE = [60, 61, 62];
const FOEIFI = [55, 56, 57, 58, 59];
const ZWEI = [66, 67, 68, 69];
const SAECHSI = [70, 71, 72, 73, 74, 75];
const VIERI = [83, 84, 85, 86, 87];
const ZWOELFI = [77, 78, 79, 80, 81, 82];
const ELFI = [88, 89, 90, 91];
const SIEBNI = [92, 93, 94, 95, 96, 97];
const ACHTI = [105, 106, 107, 108, 109];
const ZAEHNI = [99, 100, 101, 102, 103];

function run() {
    setInterval(() => {
        let timerepr = [];
    
        const date = new Date();
    
        let h = date.getHours();
        const min = date.getMinutes();
    
        timerepr.push(ES_ISCH);
    
        if ( min > 22 ) {
            h++;
        }
      
        if (   ( min >  2 && min < 23 )
            || ( min > 32 && min < 38 )
        ) {
            timerepr.push(AB);
        } else if (( min > 22 && min < 29 )
            || ( min > 37 && min < 58 )
        ) {
            timerepr.push(VOR);
        }
            
        if (   ( min >  2 && min <  8 ) 
            || ( min > 22 && min < 28 )
            || ( min > 32 && min < 38 )
            || ( min > 52 && min < 58 )
        ) {
            timerepr.push(FOEIF);
        }
        else if (   ( min >  7 && min < 13 ) 
                 || ( min > 47 && min < 53 )
        ) {
            timerepr.push(ZAEH);
        }
        else if (   ( min > 12 && min < 18 ) 
                 || ( min > 42 && min < 48 )
        ) {
            timerepr.push(VIERTEL);
        }
        else if (   ( min > 17 && min < 23 ) 
                 || ( min > 37 && min < 43 )
        ) {
            timerepr.push(ZWAENZG);
        }
        
        if (   ( min > 22 && min < 38 ) 
        ) {
            timerepr.push(HALBI);
        }
            
        switch (h) {
            case 0:
            case 12:
            case 24:
                timerepr.push(ZWOELFI);      
                break;
            case 1:
            case 13:
                timerepr.push(EIS);
                break;
            case 2:
            case 14:
                timerepr.push(ZWEI);
                break;
            case 3:
            case 15:
                timerepr.push(DRUE);
                break;
            case 4:
            case 16:
                timerepr.push(VIERI);
                break;           
            case 5:
            case 17:
                timerepr.push(FOEIFI);
                break;
            case 6:
            case 18:
                timerepr.push(SAECHSI);
                break;
            case 7:
            case 19:
                timerepr.push(SIEBNI);
                break; 
            case 8:
            case 20:
                timerepr.push(ACHTI);
                break;
            case 9:
            case 21:
                timerepr.push(NUENI);
                break;
            case 10:
            case 22:
                timerepr.push(ZAEHNI);
                break;
            case 11:
            case 23:
                timerepr.push(ELFI);
                break;            
            default:
                break;
        }

        clock.all(0, 0, 0);
        for (const led of [].concat(...timerepr)) {
            clock.set(led, 255, 255, 255);
        }

        clock.sync();

    }, 100);
}

run();