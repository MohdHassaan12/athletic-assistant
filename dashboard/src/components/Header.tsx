/*
 * Athletic Assistant XR — Header Component
 */

import { Activity, LayoutDashboard, Settings, User } from 'lucide-react';

export default function Header({ count }: { count: number }) {
  return (
    <header className="glass-card" style={{ marginBottom: '2rem', display: 'flex', justifyContent: 'space-between', alignItems: 'center', borderRadius: '1rem' }}>
      <div style={{ display: 'flex', alignItems: 'center', gap: '1rem' }}>
        <div className="pulse-glow" style={{ background: 'var(--accent-cyan)', padding: '0.5rem', borderRadius: '50%' }}>
          <Activity size={24} color="#000" />
        </div>
        <div>
          <h1 style={{ fontSize: '1.5rem', margin: 0 }}>Command Center XR</h1>
          <p style={{ fontSize: '0.8rem', opacity: 0.6 }}>Fitness Automation System • {count} Sessions Record</p>
        </div>
      </div>
      
      <nav style={{ display: 'flex', gap: '2rem' }}>
        <a href="#" style={{ color: 'var(--accent-cyan)', display: 'flex', alignItems: 'center', gap: '0.5rem', textDecoration: 'none' }}>
          <LayoutDashboard size={20} />
          <span>Dashboard</span>
        </a>
        <a href="#" style={{ opacity: 0.6, display: 'flex', alignItems: 'center', gap: '0.5rem', textDecoration: 'none' }}>
          <User size={20} />
          <span>Profile</span>
        </a>
        <a href="#" style={{ opacity: 0.6, display: 'flex', alignItems: 'center', gap: '0.5rem', textDecoration: 'none' }}>
          <Settings size={20} />
          <span>Config</span>
        </a>
      </nav>
    </header>
  );
}
