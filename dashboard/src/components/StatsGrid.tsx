/*
 * Athletic Assistant XR — Stats Grid Component
 */

import { SessionRecord } from '@/types';
import { Target, TrendingUp, Zap, Heart } from 'lucide-react';

export default function StatsGrid({ data }: { data: SessionRecord[] }) {
  const latest = data[data.length - 1];
  const averageStamina = data.reduce((acc, s) => acc + s.staminaScore, 0) / data.length;

  const stats = [
    { label: 'Current BMI', value: latest.bmi.toFixed(2), unit: 'kg/m²', icon: <Target size={24} />, color: 'var(--accent-cyan)' },
    { label: 'Average Stamina', value: averageStamina.toFixed(1), unit: 'pts', icon: <Zap size={24} />, color: 'var(--accent-green)' },
    { label: 'Latest BMR', value: Math.round(latest.bmr), unit: 'kcal', icon: <Heart size={24} />, color: 'var(--accent-red)' },
    { label: 'Target Daily', value: Math.round(latest.recommendedCalories), unit: 'kcal', icon: <TrendingUp size={24} />, color: 'var(--accent-yellow)' }
  ];

  return (
    <div className="stats-grid">
      {stats.map((s, idx) => (
        <div key={idx} className="glass-card" style={{ display: 'flex', gap: '1rem', alignItems: 'center' }}>
          <div style={{ color: s.color, background: `${s.color}22`, padding: '1rem', borderRadius: '1rem' }}>
            {s.icon}
          </div>
          <div>
            <p style={{ fontSize: '0.8rem', opacity: 0.6 }}>{s.label}</p>
            <h2 style={{ fontSize: '1.8rem', margin: 0, color: s.color, WebkitTextFillColor: s.color }}>{s.value}</h2>
            <p style={{ fontSize: '0.7rem', opacity: 0.4 }}>{s.unit}</p>
          </div>
        </div>
      ))}
    </div>
  );
}
