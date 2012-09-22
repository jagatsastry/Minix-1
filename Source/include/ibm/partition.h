/* Description of entry in partition table.  */
#ifndef _PARTITION_H
#define _PARTITION_H

/* Me:
 * 16 bytes entry of disk partition table,
 * which stores metadata about partition.
 *
 *        
 *      +-----------+
 *      |           |
 *      |   size    |
 *      |  4 bytes  |
 *      |           |
 *      +-----------+
 *      |           |
 *      |  lowsec   |
 *      |  4 bytes  |
 *      |           |
 *   8: +-----------+
 *      | last_cyl  |
 *      +-----------+
 *      | last_sec  |
 *      +-----------+
 *      | last_head |
 *      +-----------+
 *      |  sysind   |
 *   4: +-----------+
 *      | start_cyl |
 *      +-----------+
 *      | start_sec |
 *      +-----------+
 *      |start_head |
 *      +-----------+ 
 *      |  bootind  |  }--- one byte
 *   0: +-----------+ 
 *
 *
 */

struct part_entry {
  unsigned char bootind;        /* boot indicator 0/ACTIVE_FLAG; Me: nonzero if this is bootable partition. */
  unsigned char start_head;     /* head value for first sector */
  unsigned char start_sec;      /* sector value + cyl bits for first sector */
  unsigned char start_cyl;      /* track value for first sector     */
  unsigned char sysind;         /* system indicator; Me: Type of file system in this partition. Zero if partition is not being used. */
  unsigned char last_head;      /* head value for last sector     */
  unsigned char last_sec;       /* sector value + cyl bits for last sector */
  unsigned char last_cyl;       /* track value for last sector     */
  unsigned long lowsec;         /* logical first sector         */
  unsigned long size;           /* size of partition in sectors     */
};

#define ACTIVE_FLAG         0x80    /* value for active in bootind field (hd0) */
#define NR_PARTITIONS       4       /* number of entries in partition table */
#define    PART_TABLE_OFF   0x1BE   /* offset of partition table in boot sector */

/* Partition types. */
#define NO_PART             0x00    /* unused entry */
#define MINIX_PART          0x81    /* Minix partition type */

#endif /* _PARTITION_H */
