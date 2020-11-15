//
// Created by hornedheck on 15.11.2020.
//

#include "lib/lib.h"
#include <string.h>

int main() {

    print_s("STR FUNCTIONS TEST\n");

    char str[] = {
            "Am terminated it excellence invitation projection as. She graceful shy believed distance use nay. Lively is people so basket ladies window expect. Supply as so period it enough income he genius. Themselves acceptance bed sympathize get dissimilar way admiration son. Design for are edward regret met lovers. This are calm case roof and. \n"
            "\n"
            "Why end might ask civil again spoil. She dinner she our horses depend. Remember at children by reserved to vicinity. In affronting unreserved delightful simplicity ye. Law own advantage furniture continual sweetness bed agreeable perpetual. Oh song well four only head busy it. Afford son she had lively living. Tastes lovers myself too formal season our valley boy. Lived it their their walls might to by young. \n"
            "\n"
            "Spot of come to ever hand as lady meet on. Delicate contempt received two yet advanced.; Gentleman as belonging he commanded believing dejection in by. On no am winding chicken so behaved. Its preserved sex enjoyment new way behaviour. Him yet devonshire celebrated especially. Unfeeling one provision are smallness resembled repulsive. "
    };

    index(str, ';');
    index(str, '-');

    exit_proc();

}
