enum
{
	ROOTFID,
	AUTHFID
};

typedef struct FFid	FFid;
typedef struct FDir	FDir;

struct FFid
{
	FFid	*link;
	uchar	mode;
	u32int	fid;
	Qid	qid;
	u32int	iounit;
	u64int	offset;
	char	*path;
};

struct FDir
{
	FDir	*link;
	char	*path;
	Dir	*dirs;
	int	ndirs;
};

FILE	*logfile;

void	init9p();
int	_9pversion(int, u32int);
FFid	*_9pauth(int, u32int, char*);
FFid	*_9pattach(int, u32int, u32int);
FFid	*_9pwalk(int, const char*);
FFid	*_9pwalkr(int, FFid*, char*);
FFid	*fidclone(int, FFid*);
Dir	*_9pstat(int, FFid*);
int	_9pwstat(int, FFid*, Dir*);
int	_9pclunk(int, FFid*);
int	_9popen(int, FFid*);
FFid	*_9pcreate(int, FFid*, char*, int, int);
int	_9premove(int, FFid*);
int	_9pread(int, FFid*, void*, u32int);
int	_9pwrite(int, FFid*, void*, u32int);
int	_9pdirread(int, FFid*, Dir**);

Dir	*isdircached(const char*);
void	dir2stat(struct stat*, Dir*);
