int
bitcount(STYPE value)
{
    STYPE counter = 0;
    UTYPE uvalue = value;

    while (uvalue != 0) {
        counter += uvalue & 0x1;
        uvalue >>= 1;
    }

    return counter;
}
