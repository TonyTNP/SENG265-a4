#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Lab 05: Analyzing Formula 1 Race Winners by Nationality

This script processes Formula 1 race data to determine the top 10 nationalities 
with the most race wins. It does so by:
1. Loading driver and race result datasets.
2. Filtering race winners (drivers who finished in 1st place).
3. Merging winner data with driver nationality information.
4. Counting wins by nationality and displaying the top 10.

The data is read from the following provided csv files:
- 'drivers.csv': Contains driver details (e.g., driverId, nationality).
- 'results.csv': Contains race results (e.g., driverId, positionOrder).

Author: [Ashton Majachani]
Date: February 15, 2025
"""

import pandas as pd

def main():
    # Load datasets
    drivers_df = pd.read_csv('drivers.csv')
    results_df = pd.read_csv('results.csv')

    # Filter race winners (positionOrder == 1)
    winners_df = results_df[results_df['positionOrder'] == 1]

    # Merge winners with driver information
    merged_df = winners_df.merge(drivers_df, on='driverId', how='left')

    # Count winners by nationality
    top_countries = (
        merged_df.groupby('nationality')
        .size()
        .reset_index(name='win_count')
        .sort_values(by='win_count', ascending=False)
        .head(10)
    )

    # Print results
    print("Top 10 countries with most F1 race winners:")
    print(top_countries.to_string(index=False))

if __name__ == "__main__":
    main()