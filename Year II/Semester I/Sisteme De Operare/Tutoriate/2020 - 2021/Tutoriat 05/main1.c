#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
struct thread_args
{
   char *string;
   int repeat_number;
};
 
void *
repeat(void *v)
{
   struct thread_args *args = (struct thread_args *)v;
   char *string = args->string;
   int repeat_number = args->repeat_number;
   int len = strlen(string) * repeat_number;
   char *new_string = (char *)malloc(len + 1);
 
   while (repeat_number--)
   {
       strcat(new_string, string);
   }
  
   printf("Thread finished\n");
 
   return new_string;
 
   // Functia din thread aloca dinamic (pe heap) sirul nou,
   // apoi returneaza adresa acelui sir
}
 
int main()
{
 
   /*
 
   NAME
       pthread_create - create a new thread
 
   SYNOPSIS
       #include <pthread.h>
 
       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                           void *(*start_routine) (void *), void *arg);
 
       Compile and link with -pthread.
 
   DESCRIPTION
       The  pthread_create()  function  starts  a  new  thread  in the calling
       process.  The new thread starts execution by invoking  start_routine();
       arg is passed as the sole argument of start_routine().
 
       The attr argument points to a pthread_attr_t structure  whose  contents
       are  used  at  thread creation time to determine attributes for the new
       thread; this structure is initialized  using  pthread_attr_init(3)  and
       related  functions.   If  attr is NULL, then the thread is created with
       default attributes.
 
   RETURN VALUE
       On  success,  pthread_create() returns 0; on error, it returns an error
       number, and the contents of *thread are undefined.
 
   */
 
 
   // Pentru a trimite mai multe argumente catre functie prin void *arg
   // putem construi o structura care sa contina toate argumentele si sa
   // ii dam lui arg adresa obiectului.
   struct thread_args args;
   args.string = "Ceva";
   args.repeat_number = 5;
 
 
   pthread_t thr;
 
   if (pthread_create(&thr, NULL, repeat, &args))
   {
       perror(NULL);
       return errno;
   }
 
   /*
 
   NAME
       pthread_join - join with a terminated thread
 
   SYNOPSIS
       #include <pthread.h>
 
       int pthread_join(pthread_t thread, void **retval);
 
       Compile and link with -pthread.
 
   DESCRIPTION
       The pthread_join() function waits for the thread specified by thread to
       terminate.  If that thread has already terminated, then  pthread_join()
       returns immediately.  The thread specified by thread must be joinable.
 
       If  retval  is  not NULL, then pthread_join() copies the exit status of
       the target thread (i.e., the value that the target thread  supplied  to
       pthread_exit(3)) into the location pointed to by retval.  If the target
       thread was canceled, then PTHREAD_CANCELED is placed  in  the  location
       pointed to by retval.
 
   RETURN VALUE
       On success, pthread_join() returns 0; on error,  it  returns  an  error
       number.
 
   */
 
   void *result;
 
   if (pthread_join(thr, &result))
   {
       perror(NULL);
       return errno;
   }
 
   printf("Main thread received: %s\n", (char *)result);
 
   free(result);
 
   return 0;
}
