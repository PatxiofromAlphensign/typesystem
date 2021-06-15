#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <typeinfo>

#define size 512 
using namespace std;

template<typename T> 
concept ConstrainA = requires(T a){  // just to experiment with constrains
	{a < 0} -> bool;
	{a > 0} -> vector<T>;
};

template<typename T>
concept cnst =  requires(T a)  {
	//{a+=12} -> const char;
	//{a+"char"} -> string;
	{hash<T>{}(a)} -> int;
//	{onlyInt(a)+1} -> int;
};

bool onlyInt(int x) {return x==1;}

template<typename T>
class ffstm {
	public:
		T data;
		ffstm *child;
		ffstm *allocate_Tree(ffstm *tree, T *data, int n) {
			tree = new ffstm();
			if (n == sizeof(data)) return tree;
			tree->data = data[n];
			if(tree->child==NULL) tree->child = allocate_Tree(tree->child, data, n+1);
			return tree;
		}
		void printTree(ffstm *tree) {
			if(tree->child!=NULL) printTree(tree->child);
			cout <<	tree->data << endl;
		}
		int test() {return 0;}
};


typedef int (ffstm<int>::*test_f)();
typedef const filesystem::path& (filesystem::directory_entry::*path_F)() const noexcept;

template<typename T> 
T *getNames() {
	int i = 0;
	T *names = new T[size];
	for ( auto &x : filesystem::directory_iterator("./")) {
		names[i]=x.path();
		i++;
	}
	return names; 
}

filesystem::directory_entry *get() {
	filesystem::directory_entry *names = new filesystem::directory_entry [size];
	int i=0;
	for ( auto &x : filesystem::directory_iterator("./")) {
		if(x.is_directory()) {
			names[i]=x;
			i++; }
	}
	return names; 
} 

struct castS {
	filesystem::directory_entry d;
	//const filesystem::path &(filesystem::directory_entry::*path)() const noexcept;
	path_F path_f;
	int (*fp)();
	filesystem::path path_t;
};

int func() {return 0;}

template<typename T>
T cast(T a) { 
	T ptr = (T)calloc(10, sizeof(T*));
	ptr->path_f = &filesystem::directory_entry::path;
	//ptr->path = a->path; 
	return ptr;
	//is_base_of<>
}

template<cnst T> // contrianed  by hashable to int
void test(T a) {}
 
int main() {
#ifdef printf
printf("%d", x(1));
	return -1;
#endif 
	filesystem::directory_entry *d_entry = get();
	filesystem::path *d_path = getNames<filesystem::path>();

	//for (int i=0;i<sizeof(d_entry);i++) cout << d_entry[i] << endl;
	
	ffstm<filesystem::path> f;
	ffstm<filesystem::path> *k = f.allocate_Tree(&f, d_path, 0);
	//f.printTree(k);
	//printf("%d",test(2));
	filesystem::directory_entry *p = get();
	ffstm<filesystem::directory_entry> Ffstm;
	struct castS *casts;
	/* cast(casts, p); */
	//casts->path = p->path;
	struct castS *cst = cast(casts);
	//&cst->path; // TODO not a member of castS for some reason : fix it
	cst->*path_f(); // struct castS has member paht_f but it does not when dereferenced

	test_f tst = &ffstm<int>::test;

	test(2); // contrian in diverse ways possible? //note : only expressions work
	return 0;
}

