#!/usr/bin/env python3
# -*- coding: utf-8 -*-
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
    print(top_countries)

if __name__ == "__main__":
    main()