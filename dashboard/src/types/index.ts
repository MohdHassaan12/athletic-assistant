/*
 * Athletic Assistant XR — Types
 */

export interface SessionRecord {
  timestamp: string;
  userName: string;
  bmi: number;
  bmr: number;
  staminaScore: number;
  recommendedCalories: number;
  xrMode: string;
}

export interface ChartData {
  time: string;
  bmi: number;
  stamina: number;
  bmr: number;
}

export interface UserStats {
  latestBmi: number;
  latestBmr: number;
  averageStamina: number;
  totalSessions: number;
  userName: string;
}
