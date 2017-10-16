#include "farbblut.h"

Farbblut::Farbblut() {
  shader.load("shader");

  time.set(0);
  
  parameters.setName("Farbblut");
  parameters.add(speed.set("speed", 0, -5, 5));
  parameters.add(offset.set("offset", 0, 0, 1));
  parameters.add(colMix.set("colorMix", 0.5, 0, 1));
  parameters.add(lumMix.set("luminanceMix", 0.5, 0, 1));
  parameters.add(lumOff.set("luminanceOffset", 0, 0, 1));
  parameters.add(lumBse.set("luminanceBase", 0, 0, 1));
  parameters.add(bandSt.set("bandStart", 0, 0, 1));
  parameters.add(bandWt.set("bandWidth", 1, 0.01, 1));
  parameters.add(paused.set("paused", false));

  for (int i = 0; i < COLOR_STEPS; ++i)
    colors[i] = ofFloatColor::fromHsb((float)i / COLOR_STEPS, 0.6, 0.6);
}

void Farbblut::update() {
  if (!paused)
    time += speed * ofGetLastFrameTime();
}

void Farbblut::draw(ofTexture& texture, ofPlanePrimitive& plane) {
  texture.bind();
  shader.begin();
  shader.setUniform4fv("colors", (float*)colors, COLOR_STEPS);
  shader.setUniform1f("offset", (time + offset) * COLOR_STEPS);
  shader.setUniform1f("colMix", colMix);
  shader.setUniform1f("lumMix", lumMix);
  shader.setUniform1f("lumOff", lumOff);
  shader.setUniform1f("lumBse", lumBse);
  shader.setUniform1f("bandSt", bandSt);
  shader.setUniform1f("bandWt", bandWt);
  plane.draw();
  shader.end();
  texture.unbind();
}
