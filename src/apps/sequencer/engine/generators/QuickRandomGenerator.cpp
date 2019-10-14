#include "QuickRandomGenerator.h"

#include "core/utils/Random.h"

QuickRandomGenerator::QuickRandomGenerator(SequenceBuilder &builder) :
    Generator(builder)
{
    currentBeat = 0;
    update();
}

const char *QuickRandomGenerator::paramName(int index) const {
    switch (Param(index)) {
    case Param::Seed:   return "Sparse";
    case Param::Smooth: return "Medium";
    case Param::Bias:   return "Full";
    case Param::Scale:  return "Beats";
    case Param::Notes:   return "Notes";
    case Param::Last:   break;
    }
    return nullptr;
}

void QuickRandomGenerator::editParam(int index, int value, bool shift) {
    switch (Param(index)) {
      //    case Param::Seed:   setSeed(seed() + value); break;
      //    case Param::Seed:   setSeed(1); break;
    case Param::Seed:   setSeed(value); 
      //      setSmooth(0);
      //      setBias(0);
      //      setScale(0);
      break;
    case Param::Smooth: setSmooth(smooth() + value); break;
    case Param::Bias:   setBias(bias() + value); break;
    case Param::Scale:  setScale(scale() + value); break;
    case Param::Last:   break;
    }
}

void QuickRandomGenerator::printParam(int index, StringBuilder &str) const {
    switch (Param(index)) {
          case Param::Seed:   str("%d", 0); break;
      //    case Param::Seed: 
      //      if (seed() == 1) {
      //	str("Active");
      //      }
      //      else {
      //	str("-");
      //      }
      //      break;
    case Param::Smooth: str("%d", smooth()); break;
    case Param::Bias:   str("%d", bias()); break;
    case Param::Scale:  str("%d", currentBeat); break;
    case Param::Last:   break;
    }
}

void QuickRandomGenerator::update()  {
    Random rng(_seed);

    int size = _pattern.size();

    for (int i = 0; i < size; ++i) {
        _pattern[i] = rng.nextRange(255);
    }

    for (int iteration = 0; iteration < _smooth; ++iteration) {
        for (int i = 0; i < size; ++i) {
            _pattern[i] = (4 * _pattern[i] + _pattern[(i - 1 + size) % size] + _pattern[(i + 1) % size] + 3) / 6;
        }
    }

    int bias = (_bias * 255) / 10;
    int scale = _scale;
    int tmp_i;

    //    beat = rand() % 5;
    if (currentBeat > maxBeats) {
      currentBeat = 0;
    }

    for (int i = 0; i < size; ++i) {
        int value = _pattern[i];
	int complexity = rand() % 16;
        // value = ((value - 127) * scale) / 10 + 127 + bias;
	//        value = ((value + bias - 127) * scale) / 10 + 127;

	//	if (i > 31) { value = 0; }


	if (_seed < 25) {
	  if (complexity <= _seed) {
	    //	  _pattern[i] = clamp(127, 0, 255);
	    _pattern[i] = 200;
	  }
	  else {
	    //	  _pattern[i] = clamp(0, 0, 255);
	    _pattern[i] = 0;
	  }
	}


	// pick a beat pattern
	if (_seed == 25) {
	  tmp_i = i;
	  //	  if (i > 15) {
	  //	    tmp_i = 15;
	  //	  }
	  if (tmp_i != 0) {
	    tmp_i = i % 16;
	  }
	  value = beats[currentBeat][tmp_i];
	  if (value == 1) { value = value + 199; } // we mark a beat as a 1, translate that into the proper gate on value
	  _pattern[i] = value;
	}

	if (_seed == 26) {
	  value = rand() % 128;	 // pick notes in a 3 octave range
	  value = value + 80; // cut off the bottom 3 octaves
	  _pattern[i] = value;
	  //	  _pattern[i] = _tracks[0];
	}
    }

    for (size_t i = 0; i < _pattern.size(); ++i) {
        _builder.setValue(i, _pattern[i] * (1.f / 255.f));
    }

    if (_seed == 25) { currentBeat++; }

}
