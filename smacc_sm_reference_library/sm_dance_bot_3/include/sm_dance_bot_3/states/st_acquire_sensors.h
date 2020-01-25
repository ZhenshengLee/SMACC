#include <smacc/smacc.h>
namespace sm_dance_bot_3
{
struct StAcquireSensors : smacc::SmaccState<StAcquireSensors, MsDanceBotRunMode>
{
   // transition names
   // ---- TAGS ----
   struct ON_KEYBOARD : PREEMPT
   {
   };

   struct ON_KEYBOARD2 : ABORT
   {
   };

   struct ON_SENSORS_AVAILABLE : SUCCESS
   {
   };

   struct SBehav1;
   //----------------
   using SmaccState::SmaccState;

   typedef mpl::list<
       // Expected event
       //Transition<EvAllGo<SrAllEventsGo, SBehav1>, StNavigateToWaypointsX, ON_SENSORS_AVAILABLE>,
       Transition<EvAllGo<SrAllEventsGo, SBehav1>, StEventCountDown, ON_SENSORS_AVAILABLE>,

       //Transition<EvAllGo2<LuAl2>, StateDestiny2>,
       Transition<EvGlobalError, sc::deep_history<StAcquireSensors>>>
       reactions;

   static void staticConfigure()
   {
      configure_orthogonal<OrObstaclePerception, CbLidarSensor>();
      configure_orthogonal<OrStringPublisher, CbStringPublisher>("Hello World!");
      configure_orthogonal<OrTemperatureSensor, CbConditionTemperatureSensor>();
      configure_orthogonal<OrService3, CbService3>(Service3Command::SERVICE3_ON);
      configure_orthogonal<OrUpdatablePublisher, ros_publisher_client::CbDefaultPublishLoop>();

      // static_createStateReactor<SrAllEventsGo,
      //                            EvAllGo<SrAllEventsGo, SBehav1>,
      //                            mpl::list<EvTopicMessage<CbLidarSensor, OrObstaclePerception>, EvTopicMessage<CbConditionTemperatureSensor, OrTemperatureSensor>>>();

      auto srAllSensorsReady = static_createStateReactor<SrAllEventsGo>();
      srAllSensorsReady->addInputEvent<EvTopicMessage<CbLidarSensor, OrObstaclePerception>>();
      srAllSensorsReady->addInputEvent<EvTopicMessage<CbConditionTemperatureSensor, OrTemperatureSensor>>();

      srAllSensorsReady->setOutputEvent<EvAllGo<SrAllEventsGo, SBehav1>>();

      // auto sball = static_createStateReactor<SrAllEventsGo>();
      // sball->enablesOn<EvTopicMessage<CbLidarSensor, OrObstaclePerception>, EvTopicMessage<CbConditionTemperatureSensor, OrTemperatureSensor>>();
      // sball->throwsEvent<EvAllGo<SrAllEventsGo, SBehav1>>();
   }
};
} // namespace sm_dance_bot_3