
typedef struct ABin * ABin_T;
typedef void * ABinInfo;
typedef struct Iterator * Iterator_T;
typedef int (* Compare)(const void*, const void *, void *);

ABin_T ABin_init( Compare, void * );

ABinInfo ABin_insert(ABin_T, ABinInfo info);

ABinInfo ABin_search(ABin_T, ABinInfo);

ABinInfo ABin_delete(ABin_T, ABinInfo);

void ABin_destroy(ABin_T);
Iterator_T Iterator_create();
void Iterator_init(Iterator_T, ABin_T);
ABinInfo Iterator_First(Iterator_T, ABin_T);
ABinInfo Iterator_Last(Iterator_T, ABin_T);
ABinInfo Iterator_Next(Iterator_T);
ABinInfo Iterator_Prev(Iterator_T);
void Iterator_T_destroy ( Iterator_T);




