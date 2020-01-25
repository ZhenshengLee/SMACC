namespace sm_dance_bot_3
{
namespace f_pattern_states
{
template <typename SS>
struct StiFPatternRotate1 : smacc::SmaccState<StiFPatternRotate1<SS>, SS>
{
  typedef SmaccState<StiFPatternRotate1<SS>, SS> TSti;
  using TSti::SmaccState;
  using TSti::context_type;
  
  typedef smacc::Transition<EvActionSucceeded<ClMoveBaseZ, OrNavigation>, StiFPatternForward1<SS>> reactions;

  static void staticConfigure()
  {
    float angle = 0;
    double offset = 7; // for a better behaving

    if (SS::direction() == TDirection::LEFT)
      angle = 90 + offset;
    else
      angle = -90 - offset;

     //TSti::template configure_orthogonal<OrNavigation, CbRotate>(angle);
     TSti::template configure_orthogonal<OrNavigation, CbAbsoluteRotate>(angle); // absolute aligned to the y-axis
     TSti::template configure_orthogonal<OrLED, CbLEDOff>();
  }

  void runtimeConfiguration()
  {
    
  }
};
}
}