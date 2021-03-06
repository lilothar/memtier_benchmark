/*
 * Copyright (C) 2011-2017 Redis Labs Ltd.
 *
 * This file is part of memtier_benchmark.
 *
 * memtier_benchmark is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2.
 *
 * memtier_benchmark is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with memtier_benchmark.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MEMTIER_BENCHMARK_RUN_STATS_TYPES_H
#define MEMTIER_BENCHMARK_RUN_STATS_TYPES_H


class one_sec_cmd_stats {
public:
    unsigned long int m_bytes;
    unsigned long int m_ops;
    unsigned int m_hits;
    unsigned int m_misses;
    unsigned int m_moved;
    unsigned int m_ask;
    unsigned long long int m_total_latency;
    void reset();
    void merge(const one_sec_cmd_stats& other);
    void update_op(unsigned int bytes, unsigned int latency);
    void update_op(unsigned int bytes, unsigned int latency, unsigned int hits, unsigned int misses);
    void update_moved_op(unsigned int bytes, unsigned int latency);
    void update_ask_op(unsigned int bytes, unsigned int latency);
};

class one_second_stats {
public:
    unsigned int m_second;        // from start of test
    one_sec_cmd_stats m_set_cmd;
    one_sec_cmd_stats m_get_cmd;
    one_sec_cmd_stats m_wait_cmd;
    one_second_stats(unsigned int second);
    void reset(unsigned int second);
    void merge(const one_second_stats& other);
};

class totals_cmd {
public:
    double m_ops_sec;
    double m_bytes_sec;
    double m_moved_sec;
    double m_ask_sec;
    double m_latency;
    unsigned long int m_ops;
    totals_cmd();
    void add(const totals_cmd& other);
    void aggregate_average(size_t stats_size);
    void summarize(const one_sec_cmd_stats& other, unsigned long test_duration_usec);
};

class totals {
public:
    totals_cmd m_set_cmd;
    totals_cmd m_get_cmd;
    totals_cmd m_wait_cmd;
    double m_ops_sec;
    double m_bytes_sec;
    double m_hits_sec;
    double m_misses_sec;
    double m_moved_sec;
    double m_ask_sec;
    double m_latency;
    unsigned long int m_bytes;
    unsigned long int m_ops;
    totals();
    void add(const totals& other);
};


#endif //MEMTIER_BENCHMARK_RUN_STATS_TYPES_H
