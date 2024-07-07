#ifndef RECT_ID_H
#define RECT_ID_H

enum RectID {
  ID_PLAYER                   = 0,  // RED
  ID_SHOP_REPAIR              = 1,  // not used
  ID_SHOP_UPGRADE             = 2,  // not used
  ID_UNDERGROUND_EMPTY       = 4,  // BROWN + BLACK
  ID_COAL                     = 5,  // BLACK
  ID_DIRT                     = 6,  // BROWN
  ID_IRON                     = 7,  // IRONY
  ID_GOLD                     = 8,  // GOLD
  ID_TITANIUM                 = 9,  // GREEN
  ID_BEDROCK                  = 10, // BLACK
  ID_EMPTY                    = 12, // no color
  ID_FUEL_BAR                 = 13, //yellow
  ID_HEALTH_BAR               = 14, //red
  RECT_ID_SIZE
};

#endif /* RECT_ID_H */