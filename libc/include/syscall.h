#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t lead_signature;
    uint8_t reserved1[480];
    uint32_t struct_signature;
    uint32_t free_clusters;
    uint32_t next_free;
    uint8_t reserved2[12];
    uint32_t trail_signature;
} __attribute__((packed)) fat32_fsinfo_t;

typedef struct {
    char name[11];
    uint8_t attributes;
    uint8_t nt_reserved;
    uint8_t creation_time_tenths;
    uint16_t creation_time;
    uint16_t creation_date;
    uint16_t last_access_date;
    uint16_t first_cluster_high;
    uint16_t last_write_time;
    uint16_t last_write_date;
    uint16_t first_cluster_low;
    uint32_t file_size;
} __attribute__((packed)) fat32_dir_entry_t;

typedef struct {
    uint32_t lba_start;
    uint32_t bytes_per_sector;
    uint32_t sectors_per_cluster;
    uint32_t cluster_size;
    uint32_t fat_start;
    uint32_t fat_size;
    uint32_t fat_count;
    uint32_t data_start;
    uint32_t root_cluster;
    uint32_t total_clusters;
    fat32_fsinfo_t fsinfo;
} fat32_ctx_t;

typedef struct {
    fat32_ctx_t *ctx;
    uint32_t start_cluster;
    uint32_t current_cluster;
    uint32_t cluster_offset;
    uint32_t file_offset;
    uint32_t size;
    bool is_dir;
    uint32_t dir_index;
} fat32_file_t;

uint32_t sys_puts(const char* buffer, uint32_t size);
uint32_t sys_gets(char* buffer, uint32_t size);
uint32_t* sys_open(const char* path);
uint32_t sys_close(fat32_file_t* fp);
uint32_t sys_read(fat32_file_t* fp, char* buffer, uint32_t size);
uint32_t sys_read_dir(fat32_file_t* fp, fat32_dir_entry_t* entry);
uint32_t sys_write(fat32_file_t* fp, const char* buffer, uint32_t size);
uint32_t sys_seek(fat32_file_t* fp, uint32_t offset);
uint32_t sys_getsize(const char* path);
uint32_t sys_rename(const char* path, const char* new_name);
uint32_t sys_rm(const char* path);
uint32_t sys_mkdir(const char* path);
uint32_t sys_rmdir(const char* path);
uint32_t sys_getcd(char* buffer);
uint32_t sys_chdir(const char* dir);
uint32_t sys_exec(const char* path, const char** argv);
uint32_t sys_exit(uint32_t status);
uint32_t sys_sleep(uint32_t seconds);
uint32_t* sys_alloc(uint32_t size);
uint32_t sys_free(uint32_t* ptr);

#endif