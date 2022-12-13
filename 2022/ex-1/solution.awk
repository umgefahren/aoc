#!/usr/bin/awk -f


BEGIN {
        one = 0;
        two = 0;
        three = 0;
        current = 0;
}

function insert(number) {
        if (number > one) {
                three = two;
                two = one;
                one = number;
        } else if (number > two) {
                three = two;
                two = number;
        } else if (number > three) {
                three = number;
        }
}

{ 
        if ($1 == "") {
                insert(current)
                current = 0;
        } else {
                current += int($1);
        }
}

END {
        insert(current)
        print "Max " one;
        first_three = one + two + three;
        print "First Three Together " first_three;
}
