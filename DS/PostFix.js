let prompt = require('prompt-sync') ();

let eqn = prompt("Enter a Postfix Eqn : ");

function PFix(X) {
    let EQ = X.split('');
    console.log(EQ);
    let S = [];
    let d1,d2,ans;

    
    
    for (let i=0;i<EQ.length;i++) { 
        if (/[0-9]/.test(EQ[i])) {
            S.push( parseInt(EQ[i]) );
            console.log(S);
        }
        if (/[+-/*^%]/.test(EQ[i]) ) {
            switch (EQ[i]) {
                case '+' : 
                d2 = S.pop();
                d1 = S.pop();
                console.log(d1 + "+" + d2);
                ans = d1 + d2;
                break;
                
                case '-' : 
                d2 = S.pop();
                d1 = S.pop();
                console.log(d1 + "-" + d2);
                ans = d1 - d2;
                break; 

                case '/' : 
                d2 = S.pop();
                d1 = S.pop();
                console.log(d1 + "/" + d2);
                ans = d1 / d2;
                break; 

                case '*' : 
                d2 = S.pop();
                d1 = S.pop();
                console.log(d1 + "*" + d2);
                ans = d1 * d2;
                break; 

                case '^' : 
                d2 = S.pop();
                d1 = S.pop();
                console.log(d1 + "^" + d2);
                ans = Math.pow(d1,d2);
                break; 

                case '%' : 
                d2 = S.pop();
                d1 = S.pop();
                console.log(d1 + "%" + d2);
                ans = d1 % d2;
                break; 

                default : 
            }
            S.push(ans);
            console.log(S);
        }
    }
    return S;
}

console.log( PFix(eqn) );


