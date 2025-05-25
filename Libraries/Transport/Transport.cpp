#include "Transport.h"

Transport::Transport(const int BASELINE_BPM)
    : BASELINE_BPM(BASELINE_BPM)
{
    samples_for_current_beat = 0;
    beat_count = 0;
}

void Transport::prepareToPlay(const double sampleRate) { 
    SAMPLE_RATE = sampleRate; // = 48k

    // beats/second = (beats/minute) * (minutes/second)
    double beats_per_second = BASELINE_BPM / 60.0;

    // samples/beat = (samples/second) / (beats/second)
    SAMPLES_PER_BEAT = SAMPLE_RATE / beats_per_second; // = 18k

    
    // std::cout << "sample rate: " << std::to_string(SAMPLE_RATE) 
    //     << " samples/beat: " << std::to_string(SAMPLES_PER_BEAT) 
    //     << " samples/beat: " << std::to_string(static_cast<int>(SAMPLES_PER_BEAT)) 
    //     << std::endl;
}

const double Transport::processBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    const int buffer_size = bufferToFill.numSamples;
    // buffer_size ~= 480
    
    samples_for_current_beat += buffer_size;

    // get index in buffer when next beat should start
    int beat_sample_index = static_cast<int>(SAMPLES_PER_BEAT) - samples_for_current_beat;
    
    // std::cout << "buffer size: " << std::to_string(buffer_size) 
    //     << " samples: " << std::to_string(samples_for_current_beat) 
    //     << " samples/beat: " << std::to_string(static_cast<int>(SAMPLES_PER_BEAT)) 
    //     << std::endl;

    // beat starts in current buffer -> trigger beat
    if (beat_sample_index < buffer_size) {
    // if (samples_for_current_beat > static_cast<int>(SAMPLES_PER_BEAT)) {
        triggerBeat();
        samples_for_current_beat -= static_cast<int>(SAMPLES_PER_BEAT);
    }

    const double phase = samples_for_current_beat / SAMPLES_PER_BEAT;
    return phase;
}

void Transport::triggerBeat() {
    beat_count++;
    
    std::cout << "beat: " << std::to_string(beat_count) << std::endl;
}