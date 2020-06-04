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

/* file operations to implement:*/
loffset_t fop_llseek(struct file *f, loffset_t o, int whence){
  loffset_t resulting_offset;
  resulting_offset = lseek(f->file_descriptor, o, whence);
  return resulting_offset;
  //filein inodeuna git, inodeun datablocklarina git tek tek bul.
  //offset/blocksize kac blok atlamam gerekiyor? bi de modunu alcaksin
  //blockun icindeki offseti bulmak icin
}
ssize_t fop_read(struct file *f, char *buf, size_t len, loffset_t *o){
  int fd = f->file_descriptor;
  loffset_t offset = lseek(fd, o, SEEK_SET);
  read(fd, &buf, len);
  return sizeof(buf); //or len??
}
int fop_open(struct inode *i, struct file *f){
  unsigned int *ptrs_to_datablocks = i -> i_block;
  //Reading Single PTR and get direct ptrs;
  int fd = myfs -> file_descriptor;
  unsigned long blockSize = myfs->get_superblock(myfs) -> s_blocksize;
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
void sop_read_inode(struct inode *i){}
int sop_statfs(struct super_block *sb, struct kstatfs *stats){}

struct super_block *fst_get_superblock(struct file_system_type *fs){
  //I have started to implement this function as I understood
  struct super_block *super_b;
  super_b = (super_block *)malloc(sizeof(struct superblock))
  lseek(myfs.file_descriptor, BASE_OFFSET, SEEK_SET);
  read(myfs.file_descriptor, &super_b, sizeof(struct super_block));

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
  myfs.name = fs_name;
  myfs.file_descriptor = open(image_path, O_RDONLY);
  /* assign get_superblock function
     for example:
        myfs.get_superblock = your_get_superblock;
  */
  return &myfs;
}
