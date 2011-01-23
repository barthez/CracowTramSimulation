/* 
 * File:   View.h
 * Author: bartek
 *
 * Created on 19 styczeń 2011, 16:55
 */

#ifndef VIEW_H
#define	VIEW_H

#include "Surface.h"
#include <vector>
#include <string>

typedef std::vector<Surface*> SurfacePointerList;
typedef std::vector<Surface*>::iterator SPLIt;


class View {
public:
  View(Surface * display = NULL, Surface * background = NULL);
  View(const View & v);
  virtual ~View();

  void scrollAtScreenBorder(int size, int step = 5);
  bool draw();

  bool addSurface(Surface * s, int x = -1, int y = -1);
  bool removeSurface(Surface * s);

  virtual void RMBPressed(Uint16 x, Uint16 y);
  virtual void RMBReleased(Uint16 x, Uint16 y);

  virtual void MMBPressed(Uint16 x, Uint16 y);
  virtual void MMBReleased(Uint16 x, Uint16 y);

  virtual void LMBPressed(Uint16 x, Uint16 y);
  virtual void LMBReleased(Uint16 x, Uint16 y);

private:
  Surface * display;
  Surface * background;
  SurfacePointerList elements;

  void moveCrop(int x, int y);
};

#endif	/* VIEW_H */

