/*
 * Athletic Assistant XR — History Table Component
 */

import { SessionRecord } from '@/types';

export default function HistoryTable({ data }: { data: SessionRecord[] }) {
  return (
    <div className="glass-card">
      <h3 style={{ marginBottom: '1.5rem', background: 'none', WebkitTextFillColor: '#fff' }}>Recent Telemetry Sessions</h3>
      <div style={{ overflowX: 'auto' }}>
        <table style={{ width: '100%', borderCollapse: 'collapse', textAlign: 'left' }}>
          <thead>
            <tr style={{ borderBottom: '1px solid var(--card-border)', opacity: 0.6 }}>
              <th style={{ padding: '1rem' }}>Timestamp</th>
              <th style={{ padding: '1rem' }}>User</th>
              <th style={{ padding: '1rem' }}>BMI</th>
              <th style={{ padding: '1rem' }}>BMR</th>
              <th style={{ padding: '1rem' }}>Stamina</th>
              <th style={{ padding: '1rem' }}>XR Phase</th>
            </tr>
          </thead>
          <tbody>
            {data.slice().reverse().map((s, idx) => (
              <tr key={idx} style={{ borderBottom: '1px solid var(--card-border)', transition: 'background 0.2s' }}>
                <td style={{ padding: '1rem', fontSize: '0.9rem' }}>{s.timestamp.replace('T', ' ')}</td>
                <td style={{ padding: '1rem' }}>{s.userName}</td>
                <td style={{ padding: '1rem', color: 'var(--accent-cyan)' }}>{s.bmi.toFixed(2)}</td>
                <td style={{ padding: '1rem' }}>{Math.round(s.bmr)}</td>
                <td style={{ padding: '1rem', color: s.staminaScore > 150 ? 'var(--accent-green)' : 'var(--accent-yellow)' }}>{s.staminaScore.toFixed(1)}</td>
                <td style={{ padding: '1rem' }}>
                  <span style={{ 
                    background: s.xrMode === 'XR_ACTIVE' ? 'var(--accent-cyan)44' : 'rgba(255,255,255,0.1)',
                    color: s.xrMode === 'XR_ACTIVE' ? 'var(--accent-cyan)' : '#fff',
                    padding: '0.2rem 0.6rem',
                    borderRadius: '1rem',
                    fontSize: '0.75rem'
                  }}>
                    {s.xrMode}
                  </span>
                </td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    </div>
  );
}
