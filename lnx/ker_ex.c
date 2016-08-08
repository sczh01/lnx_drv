#include "linux/init.h"
#include "linux/kernel.h"
#include "linux/module.h"  
#include "linux/fs.h"
#include "asm/uaccess.h"
#include "linux/sched.h"
#include "linux/kthread.h"
#include "linux/delay.h"

static char  buf[1]="1";
static struct task_struct *my_thread=NULL;
static struct file *fp;
static mm_segment_t fs;
static loff_t pos;
#define MAX_CMD             100
#define COMMAND_BUF_SIZE    (69*MAX_CMD*4)

static struct LCM_setting_table
{
    unsigned cmd;
    unsigned char count;
    unsigned char para_list[64];
};

static struct LCM_setting_table lcm_initialization_setting[MAX_CMD];

char *FileName = "/sdd1/opt/drv/lnx/cmd.txt";

static unsigned int cmd_buf[COMMAND_BUF_SIZE];
static char* pcmd_buf;

static char* gpbuf;
static unsigned char isEnd=0;

char* get_1st_line(char* p_buf, unsigned char seperate_char){
    gpbuf = p_buf;

    while ( (*gpbuf != seperate_char) && (*gpbuf!=0) ) {
        gpbuf++;
    }

    if (*gpbuf==0) {
        isEnd = 1;
    }
    else{
        *gpbuf = 0;
    }

    return p_buf;
}

char* get_next_line(char seperate_char){

    char* plbuf = 0;

    if (isEnd) {
        return 0;
    }

    plbuf = gpbuf; //continue from get_1st_line;
    plbuf++;
    gpbuf++;

    while ((*gpbuf != seperate_char) && (*gpbuf != 0)) {
        gpbuf++;
    }

    if (*gpbuf==0) {
        isEnd = 1;
    }
    else{
        *gpbuf = 0;
    }
    //printk("debug line = %s\n", plbuf);
    return plbuf;
}

int process_cmd(char* p_buf, int buf_len )
{
    char* str;
    if( 0!=( str = get_1st_line(p_buf,'\n')) )
        printk("1st line = %s\n", str);
    else
        return 0;

    while (0!=(str = get_next_line('\n'))) {
        printk("next line = %s\n", str);
    }

    return 0;
}



int thread_func(void *data){

    while(!kthread_should_stop()){

        fs=get_fs();
        set_fs(KERNEL_DS);
        vfs_write(fp,buf,sizeof(buf),&pos);

        if(buf[0]<'9'){
            buf[0]++;
        }else{
            buf[0]='1';
        }

        set_fs(fs);
        ssleep(3);
    }
    filp_close(fp,NULL);
    return 0;
}




static int __init hello_init(void)
{
    struct inode *inode = NULL;
    int iSize;

    fp=filp_open(FileName,O_RDWR,0644);

	if(IS_ERR(fp)){
		printk("create file error\n");
		return -1;
	}

	pcmd_buf = (unsigned char*)cmd_buf;

    fs=get_fs();
    set_fs(KERNEL_DS);

    inode = fp->f_dentry->d_inode;
    iSize = inode->i_size;
    printk("file(%s) size=%d\n", FileName, iSize);

    iSize = (iSize < COMMAND_BUF_SIZE) ? iSize:COMMAND_BUF_SIZE;

    printk("file(%s) size=%d\n", FileName, iSize);

    vfs_read(fp,pcmd_buf,iSize,&pos);
    //printk("%s\n", pcmd_buf );

    filp_close(fp, 0);

    pcmd_buf[iSize] = 0;

    process_cmd(pcmd_buf, iSize);

    set_fs(fs);
    ssleep(3);
	return 0;
}

 
static void __exit hello_exit(void) {
	if(my_thread){
		printk("stop mythread\n");
		kthread_stop(my_thread);
	}
}

module_init(hello_init);  
module_exit(hello_exit); 
MODULE_LICENSE("GPL");  
MODULE_DESCRIPTION("hello");
