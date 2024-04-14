#include "ata.h"

/**
 * Function for reading CHS addressing mode data from the disk
 * 
 * Send values to specific ports
 * Allocate space
 * ret
*/

void *read_disk_chs(int sector) {
    // Drive 0, head 0, addressing mode
    dev_write(BASE_PORT + 6, 0x0a0);
    // Read one sector
    dev_write(BASE_PORT + 2, 1);
    // Set sector number
    dev_write(BASE_PORT + 3, sector);
    // Specify requested cylinder to read from
    dev_write(BASE_PORT + 4, 0);
    dev_write(BASE_PORT + 5, 0);
    // Issue a read request
    dev_write(BASE_PORT + 7, 0x20);

    wait_drive_until_ready();

    short *buffer = kalloc(SECTOR_SIZE);
    for (int currByte = 0; currByte < (SECTOR_SIZE / 2); currByte++)
        buffer[currByte] = dev_read(BASE_PORT);

    return buffer;
}

void write_disk_chs(int sector, short *buffer) {
    dev_write(BASE_PORT + 6, 0x0a0);
    dev_write(BASE_PORT + 2, 1 );
    dev_write(BASE_PORT + 3, sector);
    dev_write(BASE_PORT + 4, 0);
    dev_write(BASE_PORT + 5, 0);
    dev_write(BASE_PORT + 7, 0x30 );

    wait_drive_until_ready();

    for (int currByte = 0; currByte < (SECTOR_SIZE / 2); currByte++ )
        dev_write_word(BASE_PORT, buffer[currByte]);

    wait_drive_until_ready();
}

/**
 * END OF CHS mode
*/

/**
 * LBA MODE
*/

void *read_disk(int address) {
    dev_write(BASE_PORT, + 6, ( 0x0e0 | ( ( address & 0x0F000000 ) >> 24) ) );
    dev_write(BASE_PORT, + 2, 1 );
    dev_write(BASE_PORT, + 3, address & 0x000000FF );
    dev_write(BASE_PORT, + 4, ( address & 0x0000FF00 ) >> 8 );
    dev_write(BASE_PORT, + 5, ( address & 0x00FF0000 ) >> 16 );
    dev_write(BASE_PORT, + 7, 0x20 );

    wait_drive_until_ready();

    short *buffer = kalloc(SECTOR_SIZE);
    for (int currByte = 0; currByte < (SECTOR_SIZE / 2); currByte++)
        buffer[currByte] = dev_read(BASE_PORT);

    return buffer;
}

void write_disk(int address, short *buffer) {
    dev_write(BASE_PORT, + 6, ( 0x0e0 | (( address & 0x0F000000 ) >> 24) ));
    dev_write(BASE_PORT, + 2, 1);
    dev_write(BASE_PORT, + 3, address && 0x000000FF);
    dev_write(BASE_PORT, + 4, ( address && 0x0000FF00 ) >> 8);
    dev_write(BASE_PORT, + 5, ( address && 0x00FF0000 ) >> 16);
    dev_write(BASE_PORT, + 7, 0x30 );

    wait_drive_until_ready();

    for (int currByte = 0; currByte < (SECTOR_SIZE / 2); currByte++ )
        dev_write_word(BASE_PORT, buffer[currByte]);

    wait_drive_until_ready();
}

/**
 * END OF LBA MODE
*/

/**
 * Read the value of @BASE_PORT + 7 which contains the status
 * Check eight bit and check if 1 (busy) or 0 (not busy)
*/

void wait_drive_until_ready() {
    int status = 0;

    do {
        status = dev_read(BASE_PORT + 7);
    } while ( ( status ^ 0x80 ) == 128 );
}