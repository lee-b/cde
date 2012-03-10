/* $XConsortium: GraphicsTask.h /main/3 1996/07/18 16:46:09 drk $ */
#ifndef GRAPHICS_TASK_HDR
#define GRAPHICS_TASK_HDR

#include "Task.h"
#include "FlexBuffer.h"

#include "oliasdb/olias_consts.h"

class Token;
class SearchEngine;
class OL_Data;

class GraphicsTask : public ComplexTask {

private:
  int f_base;
  SearchEngine *f_parent;
  const FlexBuffer   *termsbuf;
  OL_Data      *graphics_data;
  OL_Data      *f_title;
  void write_record( const Token & );
  GR_TYPE graphics_type( const char * );
  
public:
  int IsDone() { return( f_base == -1 ); }
  int HasSearchTerms() const;
  const FlexBuffer *GetTerms() { return(termsbuf); }

public:
  void markup ( const Token & );
  GraphicsTask( SearchEngine *parent, const Token &t);
  
};

inline
int
GraphicsTask::HasSearchTerms() const
{
  if ( !termsbuf ) {
    return 0;
  }
  else             {
    FlexBuffer *tmpBuffer = ( FlexBuffer *)termsbuf;
    return( tmpBuffer->GetSize() );
  }
}
  

#endif
  

  
