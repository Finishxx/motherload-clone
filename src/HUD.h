#include "Player.h"
#include "RectColor.h"

/**
 * @brief Displays information regarding player on the screen at all times.
 */
class HUD : public Component {
  public:
  virtual void update() override {}
  virtual void input() override {}
  virtual void save( std::ofstream & os ) const override {}
  /**
   * @brief Constructs HUD with pointer to player, calculates location of HUD elements
   */
  HUD( Player * player );
  /**
   * @brief Draws all HUD elements
   */
  virtual void draw() const override;
  /**
   * @brief Draws fuel bar at m_FuelPos with size m_BarSize
   */
  void drawFuel() const;
  /**
   * @brief Draws health bar at m_HealthPos m_BarSize
   */
  void drawHealth() const;
  /**
   * @brief Draws Money at m_MoneyPos
   */
  void drawMoney() const;

  private:
  static HUD * m_Instance;
  Player * m_Player;
  Pos m_FuelPos;
  Pos m_HealthPos;
  Pos m_BarSize;
  Pos m_MoneyPos;

};