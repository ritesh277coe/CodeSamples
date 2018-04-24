 #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>

  #include <bits/wordsize.h>

  # if __WORDSIZE == 64
  //int dagljh
  #endif

  //Allowing entry exit functions with every function call which can help profiling.
  //https://stackoverflow.com/questions/6176284/why-doesnt-finstrument-functions-work-for-me
  //https://mcuoneclipse.com/2015/04/04/poor-mans-trace-free-of-charge-function-entryexit-trace-with-gnu-tools/
  //https://balau82.wordpress.com/2010/10/06/trace-and-profile-function-calls-with-gcc/ tells how to convert function addresses to function names
  //Use gcc -ggdb -O0 -finstrument-functions  -o t ./test.c [to compile the code with instrumentation]

  /*!
   * \brief Function which is called upon function enter. The function call is inserted by the compiler.
   * \param this_fn Address of the caller function.
   * \param call_site Return address to the function which called this_fn
   */
  __attribute__((no_instrument_function))
  void __cyg_profile_func_enter (void *func,  void *caller)
  {
B     printf("enter %p %p %lu\n", func, caller, time(NULL) );

  }

  /*!
   * \brief Function which is called upon function exit. The function call is inserted by the compiler.
   * \param this_fn Address of the caller function.
   * \param call_site Return address to the function which called this_fn
   */
  __attribute__((no_instrument_function))
  void __cyg_profile_func_exit (void *func, void *caller)
  {
B     printf("exit %p %p %lu\n", func, caller, time(NULL) );
  }

  void func()
  {
      printf("inside func\n");
  }
  int
  main(void)
  {
      long a;
      int i;
      char buf[10];
      func();
      int x = snprintf(buf, 10, "123456789123456789");
B =>  exit(EXIT_SUCCESS);
  }
