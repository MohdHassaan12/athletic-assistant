/*
 * Athletic Assistant XR — Command Center
 * Main Dashboard Entry Point
 */

import { getFitnessData } from '@/lib/data-fetcher';
import StatsGrid from '@/components/StatsGrid';
import ChartsSection from '@/components/ChartsSection';
import HistoryTable from '@/components/HistoryTable';
import Header from '@/components/Header';

export default async function DashboardPage() {
  const data = await getFitnessData();

  return (
    <div className="dashboard-container">
      <main className="main-content">
        <Header count={data.length} />
        
        {data.length > 0 ? (
          <>
            <StatsGrid data={data} />
            <ChartsSection data={data} />
            <HistoryTable data={data} />
          </>
        ) : (
          <div className="glass-card" style={{ textAlign: 'center', marginTop: '4rem' }}>
            <h2 className="accent-text-cyan">No Session Data Detected</h2>
            <p style={{ marginTop: '1rem', opacity: 0.7 }}>
              Run your C fitness application to generate logs/fitness_sessions.log.
            </p>
          </div>
        )}
      </main>
    </div>
  );
}
