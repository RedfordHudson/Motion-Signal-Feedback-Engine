#include "Transport.h"

#include <Cycle.h>

Transport::Transport(const int BASELINE_BPM, const float ratio)
    : BASELINE_BPM(BASELINE_BPM),
    cycle(std::make_unique<Cycle>(ratio))
{
    samples_for_current_beat = 0;
    beat_count = 0;
}

Transport::~Transport() {}

void Transport::prepareToPlay(const float sampleRate) { 
    SAMPLE_RATE = sampleRate; // = 48k

    // beats/second = (beats/minute) * (minutes/second)
    float beats_per_second = (float)BASELINE_BPM / 60.0f;

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

    int cycleBeatSampleIndex;

    // beat starts in current buffer -> trigger beat
    if (beatSampleIndex < buffer_size) {
        triggerBeat();

        samples_for_current_beat -= static_cast<int>(SAMPLES_PER_BEAT);

        cycle->synchronizeToTransport(samples_for_current_beat);
        cycleBeatSampleIndex = beatSampleIndex;
    }
    else {
        cycleBeatSampleIndex = cycle->processBlock(buffer_size);
    }

    phase = samples_for_current_beat / SAMPLES_PER_BEAT;
    const float cyclePhase = cycle->getPhase();


    // return std::make_tuple(beatSampleIndex, phase);
    return std::make_tuple(beatSampleIndex, phase, cycleBeatSampleIndex, cyclePhase);
}

void Transport::triggerBeat() {
    beat_count++;

    // config
    // if (beat_count % 2 == 0)
    //     cycle->updatePattern({0,4});
    // else
    //     cycle->updatePattern({0,3,6});
    
    // std::cout << "beat: " << std::to_string(beat_count) << std::endl;

}

void Transport::updateRatio(const float newRatio) {
    cycle->updateRatio(newRatio);
}


const float Transport::calculateBarPhase() const {
    return ( float( beat_count % 4 ) + phase ) / 4.0f;
}