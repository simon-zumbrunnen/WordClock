const IS_DEVELOPMENT = process.env !== 'production';

const LEDMATRIX_NUM_ROWS = 10;

const ES_ISCH = 0b110111100000;
const VIERTEL = 0b111111100000;
const FOEIF = 0b000000011110;
const ZAEH = 0b011100000000;
const ZWAENZG = 0b000001111110;
const VOR = 0b000111000000;
const AB = 0b000000011000;
const HALBI = 0b111110000000;
const NUENI = 0b000000111100;
const EIS = 0b111000000000;
const DRUE = 0b000111000000;
const FOEIFI = 0b000000111110;
const ZWEI = 0b111100000000;
const SAECHSI = 0b000011111110;
const VIERI = 0b111110000000;
const ZWOELFI = 0b000001111110;
const ELFI = 0b111100000000;
const SIEBNI = 0b000011111110;
const ACHTI = 0b111110000000;
const ZAEHNI = 0b000000111110;

function run(serialport) {
    setInterval(() => {
        let timerepr = new Array(LEDMATRIX_NUM_ROWS).fill(0);
    
        const date = new Date();
    
        let h = date.getHours();
        const min = date.getMinutes();
    
        timerepr[0] |= (ES_ISCH);
    
        if ( min > 22 ) {
            h++;
        }      
      
        if (   ( min >  2 && min < 23 )
            || ( min > 32 && min < 38 )
        ) {
            timerepr[3] |= AB;
        } else if (( min > 22 && min < 29 ) || ( min > 37 && min < 58 )) {
            timerepr[3] |= VOR;
        }
            
        if (   ( min >  2 && min <  8 ) 
            || ( min > 22 && min < 28 )
            || ( min > 32 && min < 38 )
            || ( min > 52 && min < 58 )
        ) {
            timerepr[1] |= FOEIF;
        }
        else if (   ( min >  7 && min < 13 ) 
                 || ( min > 47 && min < 53 )
        ) {
            timerepr[2] |= ZAEH;
        }
        else if (   ( min > 12 && min < 18 ) 
                 || ( min > 42 && min < 48 )
        ) {
            timerepr[1] |= VIERTEL;
        }
        else if (   ( min > 17 && min < 23 ) 
                 || ( min > 37 && min < 43 )
        ) {
            timerepr[2] |= ZWAENZG;
        }
        
        if (   ( min > 22 && min < 38 ) 
        ) {
            timerepr[4] |= HALBI;
        }
            
        switch (h) {
            case 0:
            case 12:
            case 24:
                timerepr[7] |= ZWOELFI;      
                break;
            case 1:
            case 13:
                timerepr[5] |= EIS;
                break;
            case 2:
            case 14:
                timerepr[6] |= ZWEI;
                break;
            case 3:
            case 15:
                timerepr[5] |= DRUE;
                break;
            case 4:
            case 16:
                timerepr[7] |= VIERI;
                break;           
            case 5:
            case 17:
                timerepr[5] |= FOEIFI;
                break;
            case 6:
            case 18:
                timerepr[6] |= SAECHSI;
                break;
            case 7:
            case 19:
                timerepr[8] |= SIEBNI;
                break; 
            case 8:
            case 20:
                timerepr[9] |= ACHTI;
                break;
            case 9:
            case 21:
                timerepr[4] |= NUENI;
                break;
            case 10:
            case 22:
                timerepr[9] |= ZAEHNI;
                break;
            case 11:
            case 23:
                timerepr[8] |= ELFI;
                break;            
            default:
                break;
        }

        serialport.write([0x1f, 0xff]);

        for (let row of timerepr) {
            serialport.write([row>>8, row]);
        }

        serialport.write([0xff, 0xff]);
    }, 1000)
}

const SerialPort = require('serialport');
const serialport = new SerialPort('/dev/tty.SLAB_USBtoUART');

serialport.on('open', () => {
    run(serialport);
});
serialport.on('error', error => console.log(error));
