#!/usr/bin/env python3

import datetime

def every_lab(todays_date):
    """
    Generates a list of datetime objects representing the dates 
    of all upcoming lab sessions until the end of the semester.

    Assumptions:
    - Labs occur every **Tuesday**.
    - The final lab is on **April 4, 2025**.
    - The function calculates the next Tuesday from today's date 
      and continues adding weekly lab sessions until the end date.

    Parameters:
    - todays_date (datetime.date): The current date.

    Returns:
    - List[datetime.date]: A list of dates for all remaining labs.
    """

    lab_dates = []
    end_date = datetime.date(2025, 4, 4)  # End of semester

    lab_weekday = 1  # Assuming lab is on Tuesday (Monday=0, Tuesday=1)
    days_until_tuesday = (lab_weekday - todays_date.weekday()) % 7

    # Get the next Tuesday (if today is Tuesday, use today's date)
    if days_until_tuesday == 0:
        next_lab = todays_date
    else:
        next_lab = todays_date + datetime.timedelta(days=days_until_tuesday)

    current_date = next_lab

    # Add lab dates every week until the end date
    while current_date <= end_date:
        lab_dates.append(current_date)
        current_date += datetime.timedelta(days=7)  # Move to next Tuesday

    return lab_dates


def main():
    """
    Creates a datetime object for today's date and generates a list 
    of lab session dates using `every_lab()`. Prints each date in 
    the format "Tue, 15 Jan 25".
    """

    # Get today's date
    todays_date = datetime.date.today()

    # Get all lab dates
    date_list = every_lab(todays_date)

    # Print lab dates in required format
    for lab_data in date_list:
        print(lab_data.strftime("%a, %d %b %y"))


# Correct main entry point check
if __name__ == "__main__":
    main()
