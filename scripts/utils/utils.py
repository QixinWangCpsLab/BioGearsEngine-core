import os
import random
import pandas as pd

# change cwd to root dir
os.chdir("/opt/biogears/core/runtime")

# sepsis mic values candidates
mic_sepsis_cands = ["8", "16", "4", "32"]
severity_cands = ["Mild", "Moderate", "Severe"]
treatment_plan_cands = ["None", "REFRESH", "EGDT"]
antibiodelay_cands = ["46", "32", "16", "8"]
treatmentinterv_cands = ["30", "60", "12"]


# try to do the howto-PatientGeneration (multi threading)
# firsr load the patient states file names and write them into the config file format
def prepare_config_file():
    patient_states = os.listdir("states")
    lines = []
    for file in patient_states:
        # randomly choose an severety from the list of the severity_cands
        severity = random.choice(severity_cands)
        # randomly choose an treatment plan from the list of the treatment_plan_cands
        treatment_plan = random.choice(treatment_plan_cands)
        # randomly choose an antibio delay from the list of the antibiodelay_cands
        antibio_delay = random.choice(antibiodelay_cands)
        # randomly choose an treatment interv from the list of the treatmentinterv_cands
        treatment_interv = random.choice(treatmentinterv_cands)
        # randomly choose an mic value from the list of the mic_sepsis_cands
        mic_value = random.choice(mic_sepsis_cands)
        # append the series as: Severity, PLAN, MIC, antibiodelay_cands, Interval for treatments, [file, Duration]
        line = [severity, treatment_plan, mic_value, antibio_delay, treatment_interv, 48, "states/" + file]
        lines.append(line)
    # create the dataframe
    df = pd.DataFrame(lines, columns=None)
    return df

if __name__ == "__main__":
    config_csv = prepare_config_file()
    # Define the path to the configuration CSV
    config_path = "config/patientgenconfig.csv"
    # Write "48" to a temporary file
    with open(config_path, 'w') as f:
        f.write("48\n")
    # Append the DataFrame to the file
    config_csv.to_csv(config_path, mode='a', index=False, header=False)