#include "Transport.h"

#include <Cycle.h>

Transport::Transport(const int BASELINE_BPM)
    : BASELINE_BPM(BASELINE_BPM),
    cycle(std::make_unique<Cycle>(8))
{
    samples_for_current_beat = 0;
    beat_count = 0;
}

Transport::~Transport() {}

void Transport::prepareToPlay(const float sampleRate) { 
    SAMPLE_RATE = sampleRate; // = 48k

    // beats/second = (beats/minute) * (minutes/second)
    float beats_per_second = BASELINE_BPM / 60.0;

    // samples/beat = (samples/second) / (beats/second)
    SAMPLES_PER_BEAT = SAMPLE_RATE / beats_per_second; // = 18k

    cycle->prepareToPlay(SAMPLES_PER_BEAT);

    
    // std::cout << "sample rate: " << std::to_string(SAMPLE_RATE) 
    //     << " samples/beat: " << std::to_string(SAMPLES_PER_BEAT) 
    //     << " samples/beat: " << std::to_string(static_cast<int>(SAMPLES_PER_BEAT)) 
    //     << std::endl;
}

const std::tuple<int,float,int,float> Transport::processBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    const int buffer_size = bufferToFill.numSamples; // = 480
    
    samples_for_current_beat += buffer_size;

    // get index in buffer when next beat should start
    const int beatSampleIndex = static_cast<int>(SAMPLES_PER_BEAT) - samples_for_current_beat;
    
    // std::cout << "buffer size: " << std::to_string(buffer_size) 
    //     << " samples: " << std::to_string(samples_for_current_beat) 
    //     << " samples/beat: " << std::to_string(static_cast<int>(SAMPLES_PER_BEAT)) 
    //     << std::endl;

    // beat starts in current buffer -> trigger beat
    if (beatSampleIndex < buffer_size) {
        triggerBeat();
        samples_for_current_beat -= static_cast<int>(SAMPLES_PER_BEAT);
    }

    const float phase = samples_for_current_beat / SAMPLES_PER_BEAT;

    auto [cycleBeatSampleIndex, cyclePhase] = cycle->processBlock(buffer_size);

    // return std::make_tuple(beatSampleIndex, phase);
    return std::make_tuple(beatSampleIndex, phase, cycleBeatSampleIndex, cyclePhase);
}

void Transport::triggerBeat() {
    beat_count++;

    // config
    if (beat_count % 2 == 0)
        cycle->updatePattern({0,4});
    else
        cycle->updatePattern({0,3,6});
    
    // std::cout << "beat: " << std::to_string(beat_count) << std::endl;

    cycle->resetBeatCount();
}

void Transport::modulateN(const int n) {
    cycle->modulateN(n);
}
