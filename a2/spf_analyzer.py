#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Ashton Majachani
V00990297
03.01.2025
Student Performance Factors Analyzer

Based on: https://www.kaggle.com/datasets/lainguyn123/student-performance-factors
Sample usage: python spf_analyzer.py --TASK="1"

Restrictions:
- Runs as a script.
- Uses short, well-parameterized functions.
- No global variables.
- Uses typing hints.
- Only UGLS-approved libraries (numpy, pandas) are allowed.

Usage:
- Enable tester execution: `chmod u+x tester`
- Run tests using:
  * `./tester 1` (Task 1)
  * `./tester 2` (Task 2)
  * `./tester 3` (Task 3)
  * `./tester 4` (Task 4)
  * `./tester 5` (Task 5)
- Direct execution:
  * `python spf_analyzer.py --TASK="1"`
"""

import pandas as pd
import sys
from decimal import Decimal, ROUND_HALF_UP
from typing import Any


def load_data(file_path: str) -> pd.DataFrame:
    """Load the CSV file into a pandas DataFrame."""
    return pd.read_csv(file_path)


def filter_students_by_study_hours(df: pd.DataFrame, min_hours: int = 40) -> pd.DataFrame:
    """Task 1: Filter students who studied more than a specified number of hours."""
    required_columns = {'Record_ID', 'Hours_Studied', 'Exam_Score'}
    if not required_columns.issubset(df.columns):
        raise ValueError(f"Missing required columns: {required_columns - set(df.columns)}")
    
    return df[df['Hours_Studied'] > min_hours][['Record_ID', 'Hours_Studied', 'Exam_Score']]


def top_10_high_scorers(df: pd.DataFrame) -> pd.DataFrame:
    """Task 2: Get top 10 students with Exam_Score >= 85, sorted by Exam_Score (desc) and Record_ID (asc)."""
    required_columns = {'Record_ID', 'Hours_Studied', 'Exam_Score'}
    if not required_columns.issubset(df.columns):
        raise ValueError(f"Missing required columns: {required_columns - set(df.columns)}")
    
    return (df[df['Exam_Score'] >= 85]
            .sort_values(by=['Exam_Score', 'Record_ID'], ascending=[False, True])
            [['Record_ID', 'Hours_Studied', 'Exam_Score']]
            .head(10))


def filter_students_by_attendance(df: pd.DataFrame) -> pd.DataFrame:
    """Task 3: Filter students with 100% attendance and extracurricular activities marked as 'Yes'."""
    required_columns = {'Record_ID', 'Exam_Score', 'Attendance', 'Extracurricular_Activities'}
    if not required_columns.issubset(df.columns):
        raise ValueError(f"Missing required columns: {required_columns - set(df.columns)}")
    
    return df[(df['Attendance'] == 100) & (df['Extracurricular_Activities'] == 'Yes')][['Record_ID', 'Exam_Score']]


def compute_average_attendance(df: pd.DataFrame) -> pd.DataFrame:
    """Task 4: Compute average attendance for each grade category."""
    grading_scale = {
        'A+': (90, 101), 'A': (85, 89), 'A-': (80, 84), 'B+': (77, 79), 'B': (73, 76),
        'B-': (70, 72), 'C+': (65, 69), 'C': (60, 64), 'D': (50, 59)
    }

    def get_grade(score: int) -> str:
        """Assigns a letter grade based on the Exam_Score."""
        for grade, (low, high) in grading_scale.items():
            if low <= score <= high:
                return grade
        return None

    df = df.copy()
    df['Grade'] = df['Exam_Score'].apply(get_grade)
    df.dropna(subset=['Grade'], inplace=True)

    df['Attendance'] = df['Attendance'].apply(
        lambda x: float(Decimal(str(x)).quantize(Decimal('0.1'), rounding=ROUND_HALF_UP))
    )

    avg_attendance = df.groupby('Grade', as_index=False)['Attendance'].mean()
    avg_attendance['Attendance'] = avg_attendance['Attendance'].apply(
        lambda x: float(Decimal(str(x)).quantize(Decimal('0.1'), rounding=ROUND_HALF_UP))
    )

    avg_attendance['Grade'] = pd.Categorical(avg_attendance['Grade'], categories=list(grading_scale.keys()), ordered=True)
    return avg_attendance.sort_values(by='Grade')


def compute_tutoring_stats(df: pd.DataFrame) -> pd.DataFrame:
    """Task 5: Compute grade classification and tutoring session statistics."""
    grading_scale = {
        'A': (80, 101), 'B': (70, 79), 'C': (60, 69), 'D': (50, 59), 'F': (0, 49)
    }

    def get_grade(score: int) -> str:
        """Assigns a letter grade based on the Exam_Score."""
        for grade, (low, high) in grading_scale.items():
            if low <= score <= high:
                return grade
        return None

    # Assign grades
    df = df.copy()
    df['Grade'] = df['Exam_Score'].apply(get_grade)
    df.dropna(subset=['Grade'], inplace=True)

    # Ensure Tutoring_Sessions are properly formatted
    def format_tutoring_sessions(x):
        """Ensures tutoring session values are properly formatted as int or rounded float."""
        if isinstance(x, int):  
            return x  
        elif isinstance(x, float) and x.is_integer():
            return int(x)  # Convert whole-number floats to int
        else:
            return float(Decimal(str(x)).quantize(Decimal('0.1'), rounding=ROUND_HALF_UP))

    df['Tutoring_Sessions'] = df['Tutoring_Sessions'].apply(format_tutoring_sessions)

    # Compute the average tutoring sessions per grade
    avg_tutoring = df.groupby('Grade', as_index=False)['Tutoring_Sessions'].mean()

    # Format the average tutoring sessions correctly (rounded to 1 decimal place)
    avg_tutoring['Grade_Average_Tutoring_Sessions'] = avg_tutoring['Tutoring_Sessions'].apply(
        lambda x: float(Decimal(str(x)).quantize(Decimal('0.1'), rounding=ROUND_HALF_UP))
    )
    avg_tutoring.drop(columns=['Tutoring_Sessions'], inplace=True)

    # Merge with original dataframe to get tutoring session comparison
    df = df.merge(avg_tutoring, on='Grade', how='left')

    # Check if each student's tutoring sessions are above the grade average
    df['Above_Average'] = df['Tutoring_Sessions'] > df['Grade_Average_Tutoring_Sessions']

    # Ensure proper sorting and return required columns
    return (df[['Record_ID', 'Tutoring_Sessions', 'Grade_Average_Tutoring_Sessions', 'Above_Average', 'Exam_Score', 'Grade']]
            .sort_values(by=['Exam_Score', 'Record_ID'], ascending=[False, True])
            .head(50))


def save_output(df: pd.DataFrame, output_file: str = 'output.csv') -> None:
    """Save the DataFrame to a CSV file and print it to the console."""
    df.to_csv(output_file, index=False, float_format="%.1f")  # Ensure 1 decimal place only where needed

    # Convert float values that are whole numbers into integers for display
    df = df.applymap(lambda x: int(x) if isinstance(x, float) and x.is_integer() else x)

    print(f"Output saved to {output_file}\n")
    print("Final output:")
    print(df.to_string(index=False))


def main() -> None:
    """Main entry point of the program."""
    if len(sys.argv) != 2:
        print("Usage: python spf_analyzer.py --TASK=\"<task_number>\"")
        sys.exit(1)

    task_argument: str = sys.argv[1]
    if not task_argument.startswith("--TASK="):
        print("Invalid argument format. Use --TASK=\"<task_number>\"")
        sys.exit(1)

    task_number: str = task_argument.split("=")[1].strip("\"")
    data_file: str = "data/a2-data.csv"
    df: pd.DataFrame = load_data(data_file)

    task_functions: dict[str, Any] = {
        '1': filter_students_by_study_hours,
        '2': top_10_high_scorers,
        '3': filter_students_by_attendance,
        '4': compute_average_attendance,
        '5': compute_tutoring_stats
    }

    if task_number not in task_functions:
        print("Invalid task number. Choose from 1-5.")
        sys.exit(1)

    result: pd.DataFrame = task_functions[task_number](df)
    save_output(result)


if __name__ == "__main__":
    main()
