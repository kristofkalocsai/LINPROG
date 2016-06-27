/* rounder.h
 */

class Rounder
{
public:
  virtual int Round(double) = 0;
  virtual ~Rounder(){}
};

extern "C" Rounder* create();
extern "C" void destroy(Rounder*);

typedef Rounder*(*create_t)();
typedef void(*destroy_t)(Rounder*);


