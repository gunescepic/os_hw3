#include "ext2.h"

#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BASE_OFFSET 1024 /* location of the superblock in the first group */

struct super_operations s_op;
struct inode_operations i_op;
struct file_operations f_op;

char fs_name[] = "ext2";

/* Implement functions in s_op, i_op, f_op here */

struct ext2_super_block superblock;
struct ext2_group_desc group_descr;
unsigned long blockSize;


struct super_block *fst_get_superblock(struct file_system_type *fs){
  struct super_block *super_b;
  super_b = (super_block *)malloc(sizeof(struct superblock))
  struct ext2_super_block ext2_super_b = malloc(sizeof(struct ext2_super_block));
  lseek(myfs.file_descriptor, BASE_OFFSET, SEEK_SET);

  read(myfs.file_descriptor, &ext2_super_b, sizeof(struct ext2_super_block));
  superblock = ext2_super_b;
  super_b -> s_inodes_count = ext2_super_b -> s_inodes_count;
  super_b -> s_blocks_count = ext2_super_b -> s_blocks_count;
  super_b -> s_free_blocks_count = ext2_super_b -> s_free_blocks_count;
  super_b -> s_free_inodes_count = ext2_super_b -> s_free_inodes_count;
  super_b -> s_first_data_block = ext2_super_b -> s_first_data_block;
  super_b -> s_blocksize = 1024 << ext2_super_b -> s_log_block_size;
  super_b -> s_blocksize_bits = ext2_super_b -> s_log_block_size;
  super_b -> s_blocks_per_group = ext2_super_b -> s_blocks_per_group;
  super_b -> s_inodes_per_group = ext2_super_b -> s_inodes_per_group;
  super_b -> s_minor_rev_level = ext2_super_b -> s_minor_rev_level;
  super_b -> s_rev_level = ext2_super_b -> s_rev_level;
  super_b -> s_first_ino = ext2_super_b -> s_first_ino;
  super_b -> s_inode_size = ext2_super_b -> s_inode_size;
  super_b -> s_block_group_nr = ext2_super_b -> s_block_group_nr;
  super_b -> s_maxbytes = ext2_super_b -> s_maxbytes;
  super_b -> s_magic = ext2_super_b -> s_magic;
  suber_b -> s_type = myfs;
  suber_b -> s_op = s_op;

  struct dentry *s_root;            /* Directory entry for root */
  void *s_fs_info;                  /* Filesystem private info */

  blockSize = super_b -> s_blocksize;
  lseek(myfs.file_descriptor, BASE_OFFSET + blockSize, SEEK_SET);
  read(myfs.file_descriptor, &group_descr, sizeof(ext2_group_desc));
}

unsigned int block_offset(unsigned int num_of_blocks) {
    return BASE_OFFSET + block_size * (num_of_blocks-1);
}

/* file operations to implement:*/
loffset_t fop_llseek(struct file *f, loffset_t o, int whence){
	
    // inode_table = (struct ext2_inode*)malloc(sizeof(struct ext2_inode)*superblock.s_inodes_per_group);
    struct inode_of_file = f.f_inode;
    unsigned long inode_num = inode_of_file.i_ino;
    loffset_t resulting_offset;
    lseek(myfs.file_descriptor, block_offset(group_descr.bg_inode_table + inode_num + o),whence);
}

ssize_t fop_read(struct file *f, char *buf, size_t len, loffset_t *o){
  //filein inodeuna git, inodeun datablocklarina git tek tek bul.
  //offset/blocksize kac blok atlamam gerekiyor? bi de modunu alcaksin
  //blockun icindeki offseti bulmak icin
 	direct_pointers = (unsigned int*)malloc(blockSize);
    single_pointers = (unsigned int*)malloc(blockSize);
    double_pointers = (unsigned int*)malloc(blockSize);
}
int fop_open(struct inode *i, struct file *f){
  unsigned int *ptrs_to_datablocks = i -> i_block;
  //Reading Single PTR and get direct ptrs;
  int fd = myfs -> file_descriptor;
  
  for (int j = 0; j < BLOCK_SIZE/4; j++)
  {
      if (ptrs_to_datablocks[j])
      {
        //
      }
  }

}
int fop_release(struct inode *, struct file *){

}

/*inode operations to implement:*/
struct dentry *iop_lookup(struct inode *i, struct dentry *dir){

}
int iop_readlink(struct dentry *dir, char *buf, int len){

}
int iop_readdir(struct inode *i, filldir_t callback){

}
int iop_getattr(struct dentry *dir, struct kstat *stats){}

/*superblock operations to implement:*/


/*This function assumes that only the inode number field
( i_ino ) of the passed in inode i is valid and 
the fucntion reads and populates the remaining
fields of i .*/
void sop_read_inode(struct inode *i){
  unsigned long inode_num = i-> i_no;
  int fd = myfs.file_descriptor;
  //1024--superblock--2048-- k (1024x1024/blocksize)-- 2xblocksize -- blocksize x inode_num
  unsigned int blocksize =  myfs.get_superblock(myfs)-> s_blocksize;
  int seeked_fd = lseek(fd, block_offset(group_descr.bg_inode_table) + (inode_num - 1) * sizeof(struct ext2_inode), SEEK_SET);
  struct ext2_inode *ext2_node;
  ext2_node = malloc(sizeof(struct ext2_inode));
  read(seeked_fd, &ext2_node,sizeof(struct ext2_inode));

  i -> i_mode = ext2_node -> i_mode;
  i -> i_nlink = ext2_node -> i_links_count;
  i -> i_uid = ext2_node -> i_uid;
  i -> i_gid = ext2_node -> i_gid;
  i -> i_size = ext2_node -> i_size;

  i -> i_size = ext2_node -> i_size;
  i -> i_atime = ext2_node -> i_atime;
  i -> i_mtime = ext2_node -> i_mtime;
  i -> i_ctime = ext2_node -> i_ctime;

  i -> i_blocks = ext2_node -> i_blocks;
  i -> i_block = ext2_node -> i_block;
  i -> i_op =i_op;
  i -> f_op =s_op;
  i -> i_sb = myfs.get_superblock(myfs);

  i -> i_flags = ext2_node -> i_flags;
}

int sop_statfs(struct super_block *sb, struct kstatfs *stats){
  stats = (struct kstatfs *)malloc(sizeof(kstatfs));
  stats -> f_magic = sb -> s_magic;
  stats -> f_bsize = sb -> s_blocksize;
  stats -> f_blocks = sb -> s_blocks_count;
  stats -> f_bfree = sb -> s_free_blocks_count;
  stats -> f_inodes = sb -> s_inodes_count;
  stats -> f_finodes = sb -> s_free_inodes_count;
  stats -> f_inode_size = sb -> s_inode_size;
  stats -> f_minor_rev_level = sb -> s_minor_rev_level;
  stats -> f_rev_level = sb -> s_rev_level;
  stats -> f_inode_size = sb -> s_inode_size;

  stats -> name = fs_name;
  stats -> f_namelen = strlen(fs_name);
  return 0;

}


struct file_system_type *initialize_ext2(const char *image_path) {
  /* fill super_operations s_op */
  /* fill inode_operations i_op */
  /* fill file_operations f_op */
  /* for example:
      s_op = (struct super_operations){
        .read_inode = your_read_inode_function,
        .statfs = your_statfs_function,
      };
  */
  s_op = (struct super_operations){
	    .read_inode = sop_read_inode,
	    .statfs = sop_statfs,
	  };
  i_op = (struct inode_operations){
        .readlink = iop_readlink,
        .readdir = iop_readdir,
        .lookup = iop_lookup,
        .iop_getattr = iop_getattr,
      };
  f_op = (struct file_operations){
        .llseek = fop_llseek,
        .read = fop_read,
        .open = fop_open,
        .release = fop_release,
      };

  myfs.name = fs_name;
  myfs.file_descriptor = open(image_path, O_RDONLY);
  /* assign get_superblock function
     for example:
        myfs.get_superblock = your_get_superblock;
  */
  myfs.get_superblock = fst_get_superblock;
  return &myfs;
}
