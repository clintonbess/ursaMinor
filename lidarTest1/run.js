#!/usr/bin/env shjs

require('shelljs/global');

function processResult(stdout) {  
    var lines = stdout.toString().split('\n');
    var results = new Array();
    var returnVar = 0;
    lines.forEach(function(line) {
    	if(line == 'done'){
    		returnVar = 1;
    	}
    });
    return returnVar;
};

var test = '';

var quit = 0;

// while(1){
	console.log('starting........');
	// var done = exec('./test_program /dev/ttyACM0 > test.txt');
	var done = exec('python plot.py');
// }
