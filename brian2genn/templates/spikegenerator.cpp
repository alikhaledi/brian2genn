{% extends 'common_group.cpp' %}

{% block extra_headers %}
#include "sparseProjection.h"
#include "magicnetwork_model_CODE/definitions.h"

extern unsigned int *{{_spikespace.replace('_ptr_array_','glbSpkCnt').replace('__spikespace','')}};
extern unsigned int *{{_spikespace.replace('_ptr_array_','glbSpk').replace('__spikespace','')}};
extern double t;
extern unsigned long long iT;
{% endblock %}

{% block maincode %}
    {# USES_VARIABLES { _spikespace, neuron_index, _timebins, _period_bins, _lastindex, N } #}

        const int32_t _the_period = {{_period_bins}};
        int32_t _timebin          = iT;

        if (_the_period > 0) {
            _timebin %= _the_period;
            // If there is a periodicity in the SpikeGenerator, we need to reset the
            // lastindex when the period has passed
            if ({{_lastindex}} > 0 && {{_timebins}}[{{_lastindex}} - 1] >= _timebin)
                {{_lastindex}} = 0;
        }

        int32_t _cpp_numspikes = 0;

        for(int _idx={{_lastindex}}; _idx < _num_timebins; _idx++)
        {
            if ({{_timebins}}[_idx] > _timebin)
                break;

            {{_spikespace.replace('_ptr_array_','spike_').replace('__spikespace','')}}[_cpp_numspikes++] = {{neuron_index}}[_idx];
        }

        {{_spikespace.replace('_ptr_array_','spikeCount_').replace('__spikespace','')}} = _cpp_numspikes;

        {{_lastindex}} += _cpp_numspikes;

{% endblock %}
