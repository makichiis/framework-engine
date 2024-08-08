/*
 * This is free and unencumbered software released into the public domain.
 *
 * For more information, please refer to <https://unlicense.org>
 */

//Regular text
#define ANSI_BLK "\e[0;30m"
#define ANSI_RED "\e[0;31m"
#define ANSI_GRN "\e[0;32m"
#define ANSI_YEL "\e[0;33m"
#define ANSI_BLU "\e[0;34m"
#define ANSI_MAG "\e[0;35m"
#define ANSI_CYN "\e[0;36m"
#define ANSI_WHT "\e[0;37m"

//Regular bold text
#define ANSI_BBLK "\e[1;30m"
#define ANSI_BRED "\e[1;31m"
#define ANSI_BGRN "\e[1;32m"
#define ANSI_BYEL "\e[1;33m"
#define ANSI_BBLU "\e[1;34m"
#define ANSI_BMAG "\e[1;35m"
#define ANSI_BCYN "\e[1;36m"
#define ANSI_BWHT "\e[1;37m"

//Regular underline text
#define ANSI_UBLK "\e[4;30m"
#define ANSI_URED "\e[4;31m"
#define ANSI_UGRN "\e[4;32m"
#define ANSI_UYEL "\e[4;33m"
#define ANSI_UBLU "\e[4;34m"
#define ANSI_UMAG "\e[4;35m"
#define ANSI_UCYN "\e[4;36m"
#define ANSI_UWHT "\e[4;37m"

//Regular background
#define ANSI_BLKB "\e[40m"
#define ANSI_REDB "\e[41m"
#define ANSI_GRNB "\e[42m"
#define ANSI_YELB "\e[43m"
#define ANSI_BLUB "\e[44m"
#define ANSI_MAGB "\e[45m"
#define ANSI_CYNB "\e[46m"
#define ANSI_WHTB "\e[47m"

//High intensty background 
#define ANSI_BLKHB "\e[0;100m"
#define ANSI_REDHB "\e[0;101m"
#define ANSI_GRNHB "\e[0;102m"
#define ANSI_YELHB "\e[0;103m"
#define ANSI_BLUHB "\e[0;104m"
#define ANSI_MAGHB "\e[0;105m"
#define ANSI_CYNHB "\e[0;106m"
#define ANSI_WHTHB "\e[0;107m"

//High intensty text
#define ANSI_HBLK "\e[0;90m"
#define ANSI_HRED "\e[0;91m"
#define ANSI_HGRN "\e[0;92m"
#define ANSI_HYEL "\e[0;93m"
#define ANSI_HBLU "\e[0;94m"
#define ANSI_HMAG "\e[0;95m"
#define ANSI_HCYN "\e[0;96m"
#define ANSI_HWHT "\e[0;97m"

//Bold high intensity text
#define ANSI_BHBLK "\e[1;90m"
#define ANSI_BHRED "\e[1;91m"
#define ANSI_BHGRN "\e[1;92m"
#define ANSI_BHYEL "\e[1;93m"
#define ANSI_BHBLU "\e[1;94m"
#define ANSI_BHMAG "\e[1;95m"
#define ANSI_BHCYN "\e[1;96m"
#define ANSI_BHWHT "\e[1;97m"

//Reset
#define ANSI_RESET "\e[0m"
#define ANSI_CRESET "\e[0m"
#define ANSI_COLOR_RESET "\e[0m"
