/*
 * Athletic Assistant XR — Charts Section Component
 */
'use client';

import { SessionRecord } from '@/types';
import { ResponsiveContainer, AreaChart, Area, XAxis, YAxis, CartesianGrid, Tooltip, BarChart, Bar, Cell } from 'recharts';

export default function ChartsSection({ data }: { data: SessionRecord[] }) {
  const chartData = data.slice(-10).map((s, i) => ({
    name: s.timestamp.split('T')[1].substring(0, 5),
    bmi: s.bmi,
    stamina: s.staminaScore,
  }));

  return (
    <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fit, minmax(450px, 1fr))', gap: '2rem', marginBottom: '2rem' }}>
      
      {/* BMI Trend Chart */}
      <div className="glass-card">
        <h3 style={{ marginBottom: '1.5rem', background: 'none', WebkitTextFillColor: '#fff' }}>BMI Stability Trend</h3>
        <div style={{ height: '300px', width: '100%' }}>
          <ResponsiveContainer width="100%" height="100%">
            <AreaChart data={chartData}>
              <defs>
                <linearGradient id="colorBmi" x1="0" y1="0" x2="0" y2="1">
                  <stop offset="5%" stopColor="var(--accent-cyan)" stopOpacity={0.3}/>
                  <stop offset="95%" stopColor="var(--accent-cyan)" stopOpacity={0}/>
                </linearGradient>
              </defs>
              <CartesianGrid strokeDasharray="3 3" vertical={false} stroke="rgba(255,255,255,0.05)" />
              <XAxis dataKey="name" stroke="#666" fontSize={12} tickLine={false} axisLine={false} />
              <YAxis stroke="#666" fontSize={12} tickLine={false} axisLine={false} domain={['dataMin - 1', 'dataMax + 1']} />
              <Tooltip />
              <Area type="monotone" dataKey="bmi" stroke="var(--accent-cyan)" strokeWidth={3} fillOpacity={1} fill="url(#colorBmi)" />
            </AreaChart>
          </ResponsiveContainer>
        </div>
      </div>

      {/* Stamina Progression Chart */}
      <div className="glass-card">
        <h3 style={{ marginBottom: '1.5rem', background: 'none', WebkitTextFillColor: '#fff' }}>Athletic Performance (Stamina Index)</h3>
        <div style={{ height: '300px', width: '100%' }}>
          <ResponsiveContainer width="100%" height="100%">
            <BarChart data={chartData}>
              <CartesianGrid strokeDasharray="3 3" vertical={false} stroke="rgba(255,255,255,0.05)" />
              <XAxis dataKey="name" stroke="#666" fontSize={12} tickLine={false} axisLine={false} />
              <YAxis stroke="#666" fontSize={12} tickLine={false} axisLine={false} />
              <Tooltip />
              <Bar dataKey="stamina" radius={[6, 6, 0, 0]}>
                {chartData.map((entry, index) => (
                  <Cell key={`cell-${index}`} fill={index === chartData.length - 1 ? 'var(--accent-green)' : 'rgba(0, 255, 136, 0.4)'} />
                ))}
              </Bar>
            </BarChart>
          </ResponsiveContainer>
        </div>
      </div>

    </div>
  );
}
