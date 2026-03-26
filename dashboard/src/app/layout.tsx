import './globals.css'
import type { Metadata } from 'next'

export const metadata: Metadata = {
  title: 'Athletic Assistant XR — Command Center',
  description: 'Pro-tier fitness automation dashboard for tracking BMI, Stamina, and Nutrition.',
}

export default function RootLayout({
  children,
}: {
  children: React.ReactNode
}) {
  return (
    <html lang="en">
      <body className="dashboard-theme-dark">
        {children}
      </body>
    </html>
  )
}
