#include <Arduino.h>
#include <Dezibot.h>
#include <autocharge/Autocharge.hpp>

// put function declarations here:
void start_chg(Master *master, SlaveData *slave)
{
  Serial.printf("Execute 'start_chg for slave %u'\n", slave->id);
  master->enjoinCharge(slave);
}
void end_chg(Master *master, SlaveData *slave)
{
  Serial.printf("Execute 'end_chg for slave %u'\n", slave->id);
  master->cancelCharge(slave);
}

auto chargingSlaves = Fifo<SlaveData *>();

Master master = Master(chargingSlaves,
                       start_chg,
                       end_chg);

void setup()
{
  // put your setup code here, to run once:
  delay(2000);
  Serial.begin(115200);
  Serial.println("+-------------------------+");
  Serial.println("| Charging Station Master |");
  Serial.println("+-------------------------+");
  Serial.println();
  master.begin();
  Serial.printf("NodeID '%u'\n", master.communication.getNodeId());
  master.infraredLight.front.sendFrequency(100);
}

void loop()
{
  master.step();
}
