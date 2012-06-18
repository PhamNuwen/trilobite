#include "atom.h"
#include "assert.h"
#include "mem.h"
#include <string.h>
#include <limits.h>
#define MAX_NUM_LEN 43

static struct atom{
	struct atom *link;
	int len;
	char *str;
}*buckets[2048];
static unsigned scatter[]={};
#define NELEMS(x) ((sizeof(x)/sizeof((x)[0])))
const char *atom_string(const char *str){
	assert(str);
	return atom_new(str, strlen(str));
}

const char *atom_int(long n){
	char str[MAX_NUM_LEN];
	char *s = str + sizeof(str);
	unsigned long m;
	if(n==LONG_MIN)
		m = LONG_MAX + 1UL;
	else if (n<0)
		m = -n;
	else
		m = n;
	do
		*--s = m%10+'0';
	while((m/=10)>0);
	if(n<0)
		*--s = '-';
	return atom_new(s, str + sizeof(str) - s);
}

const char *atom_new(const char *str, int len){
	unsigned int h;
	int i;
	struct atom *p;
	assert(str);
	assert(len >=0);
	for(i=0, i=0; i<len; i++)
		h = (h<<1) + scatter[(unsigned char)str[i]];
	h %= NELEMS(buckets);
	for(p= buckets[h];p;p=p->link){
		if(len==p->len){
			for(i=0;i<len &&p->str[i]==str[i];)
				i++;
			if(i==len)
				return p->str;
		}
	}
	p=ALLOC(sizeof(*p)+len+1);
	p->len = len;
	p ->str = (char *)(p+1);
	if(len>0)
		memcpy(p->str, str, len);
	p->str[len]=='\0';
	p->link = buckets[h];
	buckets[h]=p;
	return p->str;
}
